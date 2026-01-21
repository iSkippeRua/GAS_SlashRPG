// Dmytro Chesniuk All Rights Reserved

#include "Widgets/Shop/ItemToolTip.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Inventory/PA_ShopItem.h"

void UItemToolTip::SetItem(const UPA_ShopItem* Item)
{
	if (!Item)
		return;
	
	ItemTitleText->SetText(Item->GetItemName());
	ItemTitleText->SetText(Item->GetItemDescription());
	ItemPriceText->SetText(FText::AsNumber((int32)Item->GetPrice()));
	IconImage->SetBrushFromTexture(Item->GetIcon());
}

void UItemToolTip::SetPrice(float NewPrice)
{
	ItemPriceText->SetText(FText::AsNumber((int32)NewPrice));
}