// Dmytro Chesniuk All Rights Reserved

#include "Widgets/Shop/ShopWidget.h"
#include "Framework/CAssetManager.h"
#include "Widgets/Shop/ShopItemWidget.h"
#include "Components/TileView.h"
#include "Controllers/GAS_SlashHeroController.h"
#include "Shop/Shop_InteractionComponent.h"

void UShopWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetIsFocusable(true);
	
	LoadShopItems();
	
	if (ShopItemList)
	{
		ShopItemList->OnEntryWidgetGenerated().AddUObject(this, &UShopWidget::ShopItemWidgetGenerated);
	}
}

void UShopWidget::InitializeWithShop(UShop_InteractionComponent* InShopInteractionComponent, AGAS_SlashHeroController* InPlayerController)
{
	ShopInteractionComponent = InShopInteractionComponent;
	PlayerController = InPlayerController;
	
	if (!ShopInteractionComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("ShopWidget: No shop component provided!"));
		return;
	}

	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("ShopWidget: No player controller provided!"));
		return;
	}
}

void UShopWidget::OnShopMenuToggled(bool bOpen)
{
	if (bOpen)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UShopWidget::LoadShopItems()
{
	UCAssetManager::Get().LoadShopItems(
		FStreamableDelegate::CreateUObject(this, &UShopWidget::ShopItemLoadFinished)
		);
}

void UShopWidget::ShopItemLoadFinished()
{
	TArray<const UPA_ShopItem*> ShopItems;
	UCAssetManager::Get().GetLoadedShopItems(ShopItems);
	
	for (const UPA_ShopItem* ShopItem : ShopItems)
	{
		if (ShopItemList)
		{
			ShopItemList->AddItem(const_cast<UPA_ShopItem*>(ShopItem));
		}
	}
}

void UShopWidget::ShopItemWidgetGenerated(UUserWidget& NewWidget)
{
	UShopItemWidget* ItemWidget = Cast<UShopItemWidget>(&NewWidget);
	
	if (ItemWidget && ShopInteractionComponent)
	{
		ItemWidget->OnItemPurchaseIssued.AddUObject(ShopInteractionComponent, &UShop_InteractionComponent::Server_PurchaseItem);
		
		ItemsMap.Add(ItemWidget->GetShopItem(), ItemWidget);
		
		UE_LOG(LogTemp, Warning, TEXT("Shop item widget generated: %s"), *ItemWidget->GetShopItem()->GetItemName().ToString());
	}
}