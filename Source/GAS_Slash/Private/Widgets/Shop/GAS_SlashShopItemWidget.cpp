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
		if (UGAS_SlashShopComponent* ShopComponent = GetShopComponent())
		{
			int32 CurrentStock = ShopComponent->GetCurrentStock(ShopItemData);
				
			if (CurrentStock < 0)
			{
				ItemStockText->SetText(FText::FromString("Unlimited"));
			}
			else
			{
				FText StockTextFormat =	FText::Format(
					FText::FromString("Stock: {0}"),
					FText::AsNumber(CurrentStock)
				);
				ItemStockText->SetText(StockTextFormat);
			}
		}
	}
	
	if (PurchaseButton)
	{
		bool bCanPurchase = ShopItemData->IsAvailableForPurchase();
		
		if (bCanPurchase)
		{
			if (UGAS_SlashShopComponent* ShopComponent = GetShopComponent())
			{
				int32 CurrentStock = ShopComponent->GetCurrentStock(ShopItemData);
				bCanPurchase = CurrentStock < 0 || CurrentStock > 0;
			}
		}
		
		PurchaseButton->SetIsEnabled(bCanPurchase);
	}
}

void UGAS_SlashShopItemWidget::OnPurchaseButtonClicked()
{
	if (!ShopItemData)
		return;
	
	if (UGAS_SlashShopComponent* ShopComponent = GetShopComponent())
	{
		if (ShopComponent->TryPurchaseItem(ShopItemData, 1))
		{
			UpdateDisplay();
		}
	}
}

UGAS_SlashShopComponent* UGAS_SlashShopItemWidget::GetShopComponent() const
{
	if (AGAS_SlashHeroController* HeroController = Cast<AGAS_SlashHeroController>(GetOwningPlayer()))
	{
		return HeroController->FindComponentByClass<UGAS_SlashShopComponent>();
	}
	
	return nullptr;
}
