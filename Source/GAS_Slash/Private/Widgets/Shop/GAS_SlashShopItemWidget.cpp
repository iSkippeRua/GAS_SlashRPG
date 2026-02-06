#include "Widgets/Shop/GAS_SlashShopItemWidget.h"
#include "Shop/GAS_SlashShopItemData.h"
#include "Shop/GAS_SlashShopComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Controllers/GAS_SlashHeroController.h"

void UGAS_SlashShopItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (PurchaseButton)
	{
		PurchaseButton->OnClicked.AddDynamic(this, &ThisClass::OnPurchaseButtonClicked);
	}
}

void UGAS_SlashShopItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	ShopItemData = Cast<UGAS_SlashShopItemData>(ListItemObject);
	
	if (ShopItemData)
	{
		UpdateDisplay();
	}
}

void UGAS_SlashShopItemWidget::UpdateDisplay()
{
	if (!ShopItemData)
		return;
	
	if (ItemIcon && ShopItemData->GetIcon())
	{
		ItemIcon->SetBrushFromTexture(ShopItemData->GetIcon());
	}
	
	if (ItemNameText)
	{
		ItemNameText->SetText(ShopItemData->GetDisplayName());
	}
	
	if (ItemDescriptionText)
	{
		ItemDescriptionText->SetText(ShopItemData->GetItemDescription());
	}
	
	if (PriceText)
	{
		FText PriceTextFormat = FText::Format(
			FText::FromString("{0} Gold"),
			FText::AsNumber(FMath::FloorToInt(ShopItemData->GetPrice()))
		);
		
		PriceText->SetText(PriceTextFormat);
	}
	
	if (ItemStockText)
	{
		if (ShopItemData->HasUnlimitedStock())
		{
			ItemStockText->SetText(FText::FromString("Unlimited"));
		}
		else
		{
			FText ItemStockTextFormat = FText::Format(
				FText::FromString("Stock: {0}"),
				FText::AsNumber(ShopItemData->GetStockQuantity())
			);
			
			ItemStockText->SetText(ItemStockTextFormat);
		}
	}
	
	if (PurchaseButton)
	{
		const bool bCanPurchase = ShopItemData->IsAvailableForPurchase() &&
			(ShopItemData->HasUnlimitedStock() || ShopItemData->GetStockQuantity() > 0);
		
		PurchaseButton->SetIsEnabled(bCanPurchase);
	}
}

void UGAS_SlashShopItemWidget::OnPurchaseButtonClicked()
{
	if (!ShopItemData)
		return;
	
	if (AGAS_SlashHeroController* HeroController = Cast<AGAS_SlashHeroController>(GetOwningPlayer()))
	{
		if (UGAS_SlashShopComponent* ShopComponent = HeroController->FindComponentByClass<UGAS_SlashShopComponent>())
		{
			if (ShopComponent->TryPurchaseItem(ShopItemData, 1))
			{
				UpdateDisplay();
			}
		}
	}
}
