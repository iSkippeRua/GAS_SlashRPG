// Dmytro Chesniuk All Rights Reserved

#include "Inventory/PA_ShopItem.h"
#include "Items/Fragments/Inv_ItemFragment.h"

FPrimaryAssetId UPA_ShopItem::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(GetShopItemAssetType(), GetFName());
}

FPrimaryAssetType UPA_ShopItem::GetShopItemAssetType()
{
	return FPrimaryAssetType("ShopItem");
}

UTexture2D* UPA_ShopItem::GetIcon() const
{
	return Icon.LoadSynchronous();
}

bool UPA_ShopItem::GetIsStackable() const
{
	return ItemManifest.GetFragmentOfType<FInv_StackableFragment>() != nullptr;
}

bool UPA_ShopItem::GetIsConsumable() const
{
	return ItemManifest.GetFragmentOfType<FInv_ConsumableFragment>() != nullptr;
}

int32 UPA_ShopItem::GetMaxStackCount() const
{
	if (const FInv_StackableFragment* StackableFragment = ItemManifest.GetFragmentOfType<FInv_StackableFragment>())
	{
		return StackableFragment->GetMaxStackSize();
	}
	return 1;
}

FItemCollection::FItemCollection() : Items{}
{
}

FItemCollection::FItemCollection(const TArray<const UPA_ShopItem*>& InItems) : Items{InItems}
{
}

void FItemCollection::AddItem(const UPA_ShopItem* NewItem, bool bAddUnique)
{
	if (bAddUnique && Contains(NewItem))
		return;
	
	Items.Add(NewItem);
}

bool FItemCollection::Contains(const UPA_ShopItem* Item) const
{
	return Items.Contains(Item);
}

const TArray<const UPA_ShopItem*>& FItemCollection::GetItems() const
{
	return Items;
}
