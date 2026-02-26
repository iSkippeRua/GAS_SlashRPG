#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "GAS_SlashShopComponent.generated.h"

struct FOnAttributeChangeData;
class AGAS_SlashHeroController;
class UGAS_SlashShopWidget;
class UGAS_SlashShopItemData;
class UInv_InventoryComponent;
class UInv_InventoryItem;
class UGAS_SlashAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemPurchased, UGAS_SlashShopItemData*, ShopItem, int32, Quantity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShopToggled, bool, bIsOpen);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInsufficientGold);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemOutOfStock);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAS_SLASH_API UGAS_SlashShopComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UGAS_SlashShopComponent();
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	void ToggleShop();
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	void OpenShop();
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	void CloseShop();
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	bool TryPurchaseItem(UGAS_SlashShopItemData* ShopItem, int32 Quantity = 1);
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	float GetPlayerGold() const;
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	bool CanAffordItem(UGAS_SlashShopItemData* ShopItem, int32 Quantity = 1) const;
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	void LoadShopItems();
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	bool GetLoadedShopItems(TArray<UGAS_SlashShopItemData*>& OutItems) const;
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	int32 GetCurrentStock(UGAS_SlashShopItemData* ShopItem) const;
	
	bool IsShopOpen() const { return bShopOpen; }
	UGAS_SlashShopWidget* GetShopWidget() const { return ShopWidget; }
	
	FOnItemPurchased OnItemPurchased;
	FOnShopToggled OnShopToggled;
	FOnInsufficientGold OnInsufficientGold;
	FOnItemOutOfStock OnItemOutOfStock;
	
protected:
	virtual void BeginPlay() override;
	
	void OnGoldChanged(const FOnAttributeChangeData& Data);
	
	void OnShopItemsLoaded();
	void ModifyPlayerGold(float Amount);
	void SpawnPurchasedItem(UGAS_SlashShopItemData* ShopItem, int32 Quantity);
	
private:
	void ConstructShopUI();
	
	UPROPERTY()
	TWeakObjectPtr<AGAS_SlashHeroController> OwningController;
	
	UPROPERTY()
	TObjectPtr<UInv_InventoryComponent> InventoryComponent;
	
	UPROPERTY()
	TObjectPtr<UGAS_SlashAbilitySystemComponent> SlashAbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UGAS_SlashShopWidget> ShopWidget;
	
	UPROPERTY(EditAnywhere, Category = "Shop")
	TSubclassOf<UGAS_SlashShopWidget> ShopWidgetClass;
	
	UPROPERTY()
	TArray<UGAS_SlashShopItemData*> LoadedShopItems;
	
	UPROPERTY()
	TMap<UGAS_SlashShopItemData*, int32> RuntimeStockCounts;
	
	bool bShopOpen = false;
	
	UPROPERTY(EditAnywhere, Category = "Shop")
	float DropSpawnAngleMin = -90.f;

	UPROPERTY(EditAnywhere, Category = "Shop")
	float DropSpawnAngleMax = 90.f;

	UPROPERTY(EditAnywhere, Category = "Shop")
	float DropSpawnDistanceMin = 50.f;

	UPROPERTY(EditAnywhere, Category = "Shop")
	float DropSpawnDistanceMax = 125.f;

	UPROPERTY(EditAnywhere, Category = "Shop")
	float RelativeSpawnElevation = 90.f;
};