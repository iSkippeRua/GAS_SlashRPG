#include "Shop/GAS_SlashShopItemData.h"

FPrimaryAssetId UGAS_SlashShopItemData::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(GetShopItemAssetType(), GetFName());
}

FPrimaryAssetType UGAS_SlashShopItemData::GetShopItemAssetType()
{
	return FPrimaryAssetType("ShopItem");
}
