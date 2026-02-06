#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Items/Manifest/Inv_ItemManifest.h"
#include "GAS_SlashShopItemData.generated.h"

UCLASS(BlueprintType)
class GAS_SLASH_API UGAS_SlashShopItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	static FPrimaryAssetType GetShopItemAssetType();
	
	FORCEINLINE const FInv_ItemManifest& GetItemManifest() const { return ItemManifest; }
	FORCEINLINE FInv_ItemManifest& GetItemManifestMutable() { return ItemManifest; }
	
	FORCEINLINE float GetPrice() const { return ItemPrice; }
	FORCEINLINE float GetSellPrice() const { return ItemPrice * 0.5f; }
	
	FORCEINLINE const FText& GetDisplayName() const { return ItemDisplayName; }
	FORCEINLINE const FText& GetItemDescription() const { return ItemDescription; }
	FORCEINLINE UTexture2D* GetIcon() const { return ItemIcon; }
	
	FORCEINLINE bool IsAvailableForPurchase() const { return bAvailableForPurchase; }
	FORCEINLINE int32 GetStockQuantity() const { return StockQuantity; }
	FORCEINLINE bool HasUnlimitedStock() const { return bUnlimitedStock; }
	FORCEINLINE void SetStockQuantity(int32 NewQuantity) { StockQuantity = NewQuantity; }
	FORCEINLINE void DecrementStock(int32 Amount = 1) { if (!bUnlimitedStock) StockQuantity = FMath::Max(0, StockQuantity - Amount); }

	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Shop")
	FInv_ItemManifest ItemManifest;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shop")
	FText ItemDisplayName;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shop")
	FText ItemDescription;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shop")
	TObjectPtr<UTexture2D> ItemIcon;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shop")
	float ItemPrice = 100.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shop")
	bool bAvailableForPurchase = true;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shop")
	int32 StockQuantity = -1;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shop")
	bool bUnlimitedStock = true;
};