#include "Widgets/Shop/GAS_SlashShopWidget.h"
#include "Shop/GAS_SlashShopComponent.h"
#include "Shop/GAS_SlashShopItemData.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/TileView.h"

void UGAS_SlashShopWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &ThisClass::OnCloseButtonClicked);
	}
	
	UpdateGoldDisplay();
}

void UGAS_SlashShopWidget::PopulateShopItems(const TArray<UGAS_SlashShopItemData*>& ShopItems)
{
	if (!ShopItemListView)
		return;
	
	ShopItemListView->ClearListItems();
	
	for (UGAS_SlashShopItemData* ShopItem : ShopItems)
	{
		if (ShopItem && ShopItem->IsAvailableForPurchase())
		{
			ShopItemListView->AddItem(ShopItem);
		}
	}
	
	UpdateGoldDisplay();
}

void UGAS_SlashShopWidget::SetShopComponent(UGAS_SlashShopComponent* InShopComponent)
{
	ShopComponent = InShopComponent;
	
	if (ShopComponent)
	{
		ShopComponent->OnItemPurchased.AddDynamic(this, &ThisClass::OnItemPurchasedHandler);
	}
}

void UGAS_SlashShopWidget::OnItemPurchasedHandler(UGAS_SlashShopItemData* ShopItem, int32 Quantity)
{
	UpdateGoldDisplay();
}

void UGAS_SlashShopWidget::UpdateGoldDisplay()
{
	if (!GoldAmountText || !ShopComponent)
		return;
	
	const float CurrentGold = ShopComponent->GetPlayerGold();
	GoldAmountText->SetText(FText::AsNumber(FMath::FloorToInt(CurrentGold)));
}

void UGAS_SlashShopWidget::OnCloseButtonClicked()
{
	if (ShopComponent)
	{
		ShopComponent->CloseShop();
	}
}
