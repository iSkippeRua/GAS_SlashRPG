// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "Inventory/PA_ShopItem.h"
#include "CAssetManager.generated.h"

UCLASS()
class GAS_SLASH_API UCAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static UCAssetManager& Get();
	
	void LoadShopItems(const FStreamableDelegate& LoadFinishedCallback);
	bool GetLoadedShopItems(TArray<const UPA_ShopItem*>& OutItems) const;
	const TMap<const UPA_ShopItem*, FItemCollection>& GetCombinationMap() const { return CombinationMap; }
	const TMap<const UPA_ShopItem*, FItemCollection>& GetIngredientMap() const { return IngredientMap; }
	
private:
	void ShopItemLoadFinished(FStreamableDelegate Callback);
	void BuildItemMaps();
	void AddToCombinationMap(const UPA_ShopItem* Ingredient, const UPA_ShopItem* CombinationItem);
	
	UPROPERTY()
	TMap<const UPA_ShopItem*, FItemCollection> CombinationMap;
	
	UPROPERTY()
	TMap<const UPA_ShopItem*, FItemCollection> IngredientMap;
};