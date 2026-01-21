// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Items/Manifest/Inv_ItemManifest.h"
#include "PA_ShopItem.generated.h"

class UPA_ShopItem;

USTRUCT(BlueprintType)
struct FItemCollection
{
	GENERATED_BODY()
	
public:
	FItemCollection();
	FItemCollection(const TArray<const UPA_ShopItem*>& InItems);
	void AddItem(const UPA_ShopItem* NewItem, bool bAddUnique = false);
	bool Contains(const UPA_ShopItem* Item) const;
	const TArray<const UPA_ShopItem*>& GetItems() const;
	
private:
	TArray<const UPA_ShopItem*> Items;
};

UCLASS()
class GAS_SLASH_API UPA_ShopItem : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	static FPrimaryAssetType GetShopItemAssetType();
	
	UTexture2D* GetIcon() const;
	FText GetItemName() const { return ItemName; }
	FText GetItemDescription() const { return ItemDescription; }
	float GetPrice() const { return Price; }
	float GetSellPrice() const { return Price * 0.5f; }
	
	UFUNCTION(BlueprintCallable, Category = "ShopItem")
	bool GetIsStackable() const;
	
	UFUNCTION(BlueprintCallable, Category = "ShopItem")
	bool GetIsConsumable() const;
	
	UFUNCTION(BlueprintCallable, Category = "ShopItem")
	int32 GetMaxStackCount() const;
	
	const TArray<TSoftObjectPtr<UPA_ShopItem>>& GetIngredients() const { return IngredientItems; }
	
	UFUNCTION(BlueprintCallable, Category = "ShopItem")
	const FInv_ItemManifest& GetItemManifest() const { return ItemManifest; }
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	TSoftObjectPtr<UTexture2D> Icon;
	
	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	float Price;
	
	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	FText ItemName;
	
	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	FText ItemDescription;
	
	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	TArray<TSoftObjectPtr<UPA_ShopItem>> IngredientItems;
	
	UPROPERTY(EditDefaultsOnly, Category = "ShopItem")
	FInv_ItemManifest ItemManifest;
};