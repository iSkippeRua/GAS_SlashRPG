// Dmytro Chesniuk All Rights Reserved

#include "Widgets/Shop/ShopItemWidget.h"
#include "Inventory/PA_ShopItem.h"

void UShopItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	ShopItem = Cast<UPA_ShopItem>(ListItemObject);
	
	if (!ShopItem)
	{
		return;
	}
	
	SetIcon(ShopItem->GetIcon());
}

void UShopItemWidget::RightMouseButtonClicked()
{
	if (ShopItem)
	{
		OnItemPurchaseIssued.Broadcast(ShopItem, 1);
	}
}