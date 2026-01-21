#include "Shop/Shop_InteractionComponent.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "Items/Inv_InventoryItem.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/GAS_SlashAttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "Characters/GAS_SlashBaseCharacter.h"
#include "Controllers/GAS_SlashHeroController.h"
#include "Inventory/PA_ShopItem.h"
#include "Widgets/Shop/ShopWidget.h"

class UGAS_SlashAttributeSet;

UShop_InteractionComponent::UShop_InteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UShop_InteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UShop_InteractionComponent::OnPlayerEnterShopArea(AGAS_SlashHeroController* PlayerController)
{
	if (!IsValid(PlayerController))
		return;
	
	CurrentPlayerController = PlayerController;
	
	OnShopInteractionAvailable.Broadcast(true);
	
	UE_LOG(LogTemp, Warning, TEXT("Player entered shop area"));
}

void UShop_InteractionComponent::OnPlayerLeaveShopArea(AGAS_SlashHeroController* PlayerController)
{
	if (!IsValid(PlayerController))
		return;
	
	if (bShopMenuOpen)
	{
		ToggleShopMenu();
	}
	
	OnShopInteractionAvailable.Broadcast(false);
	
	CurrentPlayerController = nullptr;
	UE_LOG(LogTemp, Warning, TEXT("Player left shop area"));
}

void UShop_InteractionComponent::ToggleShopMenu()
{
	if (!CurrentPlayerController.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot toggle shop - no player in area."));
		return;
	}
	
	bShopMenuOpen = !bShopMenuOpen;
	OnShopMenuToggled.Broadcast(bShopMenuOpen);
	
	if (bShopMenuOpen)
	{
		CreateShopWidget();
		OnGoldUpdated.Broadcast(GetPlayerGold());
		UE_LOG(LogTemp, Warning, TEXT("Shop menu open."));
	}
	else
	{
		DestroyShopWidget();
		UE_LOG(LogTemp, Warning, TEXT("Shop menu closed."));
	}
}

void UShop_InteractionComponent::Server_PurchaseItem_Implementation(const UPA_ShopItem* ItemToPurchase, int32 Quantity)
{
	if (!CurrentPlayerController.IsValid())
	{
		OnPurchaseFailed.Broadcast(FText::FromString("No player controller."), 0);
		return;
	}
	
	if (!IsValid(ItemToPurchase) || Quantity <= 0)
	{
		OnPurchaseFailed.Broadcast(FText::FromString("Invalid purchase"), 1);
		return;
	}
	
	float TotalPrice = ItemToPurchase->GetPrice() * Quantity;
	float PlayerGold = GetPlayerGold();
	
	if (PlayerGold < TotalPrice)
	{
		OnPurchaseFailed.Broadcast(
			FText::FromString(FString::Printf(TEXT("Not enough gold. Need %.0f, have %.0f"), TotalPrice, PlayerGold)),
			2
		);
		return;
	}
	
	UInv_InventoryComponent* PlayerInventory = GetPlayerInventoryComponent();
	if (!IsValid(PlayerInventory))
	{
		OnPurchaseFailed.Broadcast(FText::FromString("No inventory found"), 3);
		return;
	}
	
	const FInv_ItemManifest& ItemManifest = ItemToPurchase->GetItemManifest();
	
	for (int32 i = 0; i < Quantity; ++i)
	{
		UInv_ItemComponent* NewItemComponent = NewObject<UInv_ItemComponent>();
		NewItemComponent->InitItemManifest(ItemManifest);
		PlayerInventory->TryAddItem(NewItemComponent);
	}
	
	ModifyPlayerGold(-TotalPrice);
	
	OnPurchaseSuccess.Broadcast(ItemToPurchase, Quantity);
	OnGoldUpdated.Broadcast(GetPlayerGold());
	
	UE_LOG(
		LogTemp, 
		Warning, 
		TEXT("Successfully purchased %d x %s for %.0f gold"),
		Quantity, *ItemToPurchase->GetItemName().ToString(), TotalPrice
	);
}

void UShop_InteractionComponent::Server_SellItem_Implementation(const FGameplayTag& ItemTag, int32 Quantity)
{
	if (!CurrentPlayerController.IsValid())
	{
		OnPurchaseFailed.Broadcast(FText::FromString("No player controller."), 0);
		return;
	}
	
	if (Quantity <= 0)
	{
		OnSellFailed.Broadcast(FText::FromString("Invalid sale"), 1);
		return;
	}
	
	UInv_InventoryComponent* PlayerInventory = GetPlayerInventoryComponent();
	if (!IsValid(PlayerInventory))
	{
		OnSellFailed.Broadcast(FText::FromString("No inventory found"), 2);
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Sell Action Activated. TODO: Implement actual sell logic."));
}

float UShop_InteractionComponent::GetPlayerGold() const
{
	bool bFound = false;
	if (UAbilitySystemComponent* AbilitySystemComponent = GetPlayerAbilitySystemComponent())
	{
		float Gold = AbilitySystemComponent->GetGameplayAttributeValue(
			UGAS_SlashAttributeSet::GetGoldAttribute(),
			bFound
		);
		if (bFound)
		{
			return Gold;
		}
	}
	
	return 0.f;
}

void UShop_InteractionComponent::ModifyPlayerGold(float Amount)
{
	UAbilitySystemComponent* AbilitySystemComponent = GetPlayerAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent))
		return;
	
	AbilitySystemComponent->ApplyModToAttribute(
		UGAS_SlashAttributeSet::GetGoldAttribute(),
		EGameplayModOp::Additive,
		Amount
	);
}

UInv_InventoryComponent* UShop_InteractionComponent::GetPlayerInventoryComponent() const
{
	if (!CurrentPlayerController.IsValid() || !IsValid(CurrentPlayerController->GetPawn()))
		return nullptr;
	
	return CurrentPlayerController->GetPawn()->FindComponentByClass<UInv_InventoryComponent>();
}

UAbilitySystemComponent* UShop_InteractionComponent::GetPlayerAbilitySystemComponent() const
{
	if (!CurrentPlayerController.IsValid() || !IsValid(CurrentPlayerController->GetPawn()))
		return nullptr;
	
	AGAS_SlashBaseCharacter* SlashCharacter = Cast<AGAS_SlashBaseCharacter>(CurrentPlayerController->GetPawn());
	if (!SlashCharacter)
		return nullptr;
	
	return SlashCharacter->GetAbilitySystemComponent();
}

void UShop_InteractionComponent::CreateShopWidget()
{
	if (!CurrentPlayerController.IsValid() || !ShopWidgetClass)
		return;
	
	ShopWidgetInstance = CreateWidget<UShopWidget>(CurrentPlayerController.Get(), ShopWidgetClass);
	if (ShopWidgetInstance)
	{
		ShopWidgetInstance->InitializeWithShop(this, CurrentPlayerController.Get());
		ShopWidgetInstance->OnShopMenuToggled(true);
		ShopWidgetInstance->AddToViewport(100);
		
		CurrentPlayerController->SetInputMode(FInputModeGameAndUI());
		CurrentPlayerController->bShowMouseCursor = true;
	}
}

void UShop_InteractionComponent::DestroyShopWidget()
{
	if (ShopWidgetInstance)
	{
		ShopWidgetInstance->RemoveFromParent();
		ShopWidgetInstance = nullptr;
	}
	
	if (CurrentPlayerController.IsValid())
	{
		CurrentPlayerController->SetInputMode(FInputModeGameOnly());
		CurrentPlayerController->bShowMouseCursor = false;
	}
}