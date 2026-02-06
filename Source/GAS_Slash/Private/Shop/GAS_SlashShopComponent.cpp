#include "Shop/GAS_SlashShopComponent.h"
#include "Shop/GAS_SlashShopItemData.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Items/Inv_InventoryItem.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "Items/Fragments/Inv_ItemFragment.h"
#include "Widgets/Shop/GAS_SlashShopWidget.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/GAS_SlashAbilitySystemComponent.h"
#include "AbilitySystem/GAS_SlashAttributeSet.h"
#include "Characters/GAS_SlashHeroCharacter.h"
#include "Controllers/GAS_SlashHeroController.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

UGAS_SlashShopComponent::UGAS_SlashShopComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGAS_SlashShopComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwningController = Cast<AGAS_SlashHeroController>(GetOwner());
	checkf(OwningController.IsValid(), TEXT("Shop Component should have a Slash Player Controller as an Owner"));
	
	InventoryComponent = OwningController->FindComponentByClass<UInv_InventoryComponent>();
	
	if (AGAS_SlashBaseCharacter* SlashCharacter = Cast<AGAS_SlashBaseCharacter>(OwningController->GetPawn()))
	{
		SlashAbilitySystemComponent = SlashCharacter->GetSlashAbilitySystemComponent();
	}
	
	if (OwningController->IsLocalController())
	{
		ConstructShopUI();
	}
	
	LoadShopItems();
}

void UGAS_SlashShopComponent::ToggleShop()
{
	if (bShopOpen)
	{
		CloseShop();
	}
	else
	{
		OpenShop();
	}
}

void UGAS_SlashShopComponent::OpenShop()
{
	if (!IsValid(ShopWidget))
		return;
	
	ShopWidget->SetVisibility(ESlateVisibility::Visible);
	bShopOpen = true;
	
	OnShopToggled.Broadcast(true);
	
	if (OwningController.IsValid())
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(ShopWidget->TakeWidget());
		OwningController->SetInputMode(InputMode);
		OwningController->SetShowMouseCursor(true);
	}
}

void UGAS_SlashShopComponent::CloseShop()
{
	if (!IsValid(ShopWidget))
		return;
	
	ShopWidget->SetVisibility(ESlateVisibility::Collapsed);
	bShopOpen = false;
	
	OnShopToggled.Broadcast(false);
	
	if (OwningController.IsValid())
	{
		FInputModeGameOnly InputMode;
		OwningController->SetInputMode(InputMode);
		OwningController->SetShowMouseCursor(false);
	}
}

bool UGAS_SlashShopComponent::TryPurchaseItem(UGAS_SlashShopItemData* ShopItem, int32 Quantity)
{
	if (!ShopItem || Quantity <= 0)
		return false;
	
	if (!ShopItem->IsAvailableForPurchase())
		return false;
	
	if (!ShopItem->HasUnlimitedStock() && ShopItem->GetStockQuantity() < Quantity)
	{
		OnItemOutOfStock.Broadcast();
		return false;
	}
	
	const float TotalCost = ShopItem->GetPrice() * Quantity;
	if (!CanAffordItem(ShopItem, Quantity))
	{
		OnInsufficientGold.Broadcast();
		return false;
	}
	
	ModifyPlayerGold(-TotalCost);
	
	if (!ShopItem->HasUnlimitedStock())
	{
		ShopItem->DecrementStock(Quantity);
	}
	
	SpawnPurchasedItem(ShopItem, Quantity);
	OnItemPurchased.Broadcast(ShopItem, Quantity);
	
	UE_LOG(LogTemp, Log, TEXT("Purchased %d x %s for %.2f gold"), 
		Quantity, 
		*ShopItem->GetItemManifest().GetItemType().ToString(), 
		TotalCost
	);
	
	return true;
}

void UGAS_SlashShopComponent::SpawnPurchasedItem(UGAS_SlashShopItemData* ShopItem, int32 Quantity)
{
	if (!IsValid(InventoryComponent) || !ShopItem)
		return;
	
	FInv_ItemManifest& ItemManifest = ShopItem->GetItemManifestMutable();
	
	if (FInv_StackableFragment* StackableFragment = ItemManifest.GetFragmentOfTypeMutable<FInv_StackableFragment>())
	{
		StackableFragment->SetStackCount(Quantity);
	}
	
	if (APawn* PlayerPawn = OwningController->GetPawn())
	{
		FVector RotatedForward = PlayerPawn->GetActorForwardVector();
		RotatedForward = RotatedForward.RotateAngleAxis(FMath::FRandRange(DropSpawnAngleMin, DropSpawnAngleMax), FVector::UpVector);
		
		FVector SpawnLocation = PlayerPawn->GetActorLocation() + RotatedForward * FMath::FRandRange(DropSpawnDistanceMin, DropSpawnDistanceMax);
		SpawnLocation.Z -= RelativeSpawnElevation;
		
		const FRotator SpawnRotation = FRotator::ZeroRotator;
		
		ItemManifest.SpawnPickUpActor(this, SpawnLocation, SpawnRotation);
	}
}

float UGAS_SlashShopComponent::GetPlayerGold() const
{
	if (SlashAbilitySystemComponent)
	{
		bool bFound = false;
		
		float Gold = SlashAbilitySystemComponent->GetGameplayAttributeValue(
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

void UGAS_SlashShopComponent::ModifyPlayerGold(float Amount)
{
	if (!IsValid(SlashAbilitySystemComponent))
		return;
	
	SlashAbilitySystemComponent->ApplyModToAttribute(
		UGAS_SlashAttributeSet::GetGoldAttribute(),
		EGameplayModOp::Additive,
		Amount
	);
}

bool UGAS_SlashShopComponent::CanAffordItem(UGAS_SlashShopItemData* ShopItem, int32 Quantity) const
{
	if (!ShopItem)
		return false;
	
	const float TotalCost = ShopItem->GetPrice() * Quantity;
	return GetPlayerGold() >= TotalCost;
}

void UGAS_SlashShopComponent::LoadShopItems()
{
	UAssetManager& AssetManager = UAssetManager::Get();
	
	TArray<FPrimaryAssetId> ShopItemIds;
	AssetManager.GetPrimaryAssetIdList(UGAS_SlashShopItemData::GetShopItemAssetType(), ShopItemIds);
	
	if (ShopItemIds.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No shop items found to load"));
		return;
	}
	
	FStreamableManager& StreamableManager = AssetManager.GetStreamableManager();
	
	TArray<FSoftObjectPath> ItemsToLoad;
	for (const FPrimaryAssetId& AssetId : ShopItemIds)
	{
		FSoftObjectPath AssetPath = AssetManager.GetPrimaryAssetPath(AssetId);
		if (AssetPath.IsValid())
		{
			ItemsToLoad.Add(AssetPath);
		}
	}
	
	StreamableManager.RequestAsyncLoad(
		ItemsToLoad,
		FStreamableDelegate::CreateUObject(this, &UGAS_SlashShopComponent::OnShopItemsLoaded)
	);
}

bool UGAS_SlashShopComponent::GetLoadedShopItems(TArray<UGAS_SlashShopItemData*>& OutItems) const
{
	OutItems = LoadedShopItems;
	return OutItems.Num() > 0;
}

void UGAS_SlashShopComponent::OnShopItemsLoaded()
{
	UAssetManager& AssetManager = UAssetManager::Get();
	
	TArray<UObject*> LoadedObjects;
	AssetManager.GetPrimaryAssetObjectList(UGAS_SlashShopItemData::GetShopItemAssetType(), LoadedObjects);
	
	LoadedShopItems.Empty();
	for (UObject* Object : LoadedObjects)
	{
		if (UGAS_SlashShopItemData* ShopItem = Cast<UGAS_SlashShopItemData>(Object))
		{
			LoadedShopItems.Add(ShopItem);
		}
	}
	
	if (IsValid(ShopWidget))
	{
		ShopWidget->PopulateShopItems(LoadedShopItems);
	}
	
	UE_LOG(LogTemp, Log, TEXT("Loaded %d shop items"), LoadedShopItems.Num());
}

void UGAS_SlashShopComponent::ConstructShopUI()
{
	if (!OwningController.IsValid() || !ShopWidgetClass)
		return;
	
	ShopWidget = CreateWidget<UGAS_SlashShopWidget>(OwningController.Get(), ShopWidgetClass);
	if (ShopWidget)
	{
		ShopWidget->AddToViewport();
		ShopWidget->SetShopComponent(this);
		CloseShop();
	}
}
