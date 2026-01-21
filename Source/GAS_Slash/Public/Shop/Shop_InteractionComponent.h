// Dmytro Chesniuk All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Shop_InteractionComponent.generated.h"

class UShopWidget;
class AGAS_SlashHeroController;
struct FGameplayTag;
class UPA_ShopItem;
class UInv_InventoryComponent;
class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShopMenuToggled, bool, bOpen);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPurchaseSuccess, const UPA_ShopItem*, Item, int32, Quantity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPurchaseFailed, FText, Reason, int32, ErrorCode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSellSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSellFailed, FText, Reason, int32, ErrorCode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoldUpdated, float, NewGold);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShopInteractionAvailable, bool, bAvailable);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class GAS_SLASH_API UShop_InteractionComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UShop_InteractionComponent();
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	void OnPlayerEnterShopArea(AGAS_SlashHeroController* PlayerController);
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	void OnPlayerLeaveShopArea(AGAS_SlashHeroController* PlayerController);
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	void ToggleShopMenu();
	
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Shop")
	void Server_PurchaseItem(const UPA_ShopItem* ItemToPurchase, int32 Quantity = 1);
	
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Shop")
	void Server_SellItem(const FGameplayTag& ItemTag, int32 Quantity = 1);
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	float GetPlayerGold() const;
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	bool IsPlayerInShopArea() const { return CurrentPlayerController.IsValid(); }
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	bool IsShopMenuOpen() const { return bShopMenuOpen; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	TSubclassOf<UShopWidget> ShopWidgetClass;
	
	UPROPERTY()
	UShopWidget* ShopWidgetInstance;
	
	FOnShopMenuToggled OnShopMenuToggled;
	FOnPurchaseSuccess OnPurchaseSuccess;
	FOnPurchaseFailed OnPurchaseFailed;
	FOnSellSuccess OnSellSuccess;
	FOnSellFailed OnSellFailed;
	FOnGoldUpdated OnGoldUpdated;
	FOnShopInteractionAvailable OnShopInteractionAvailable;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	float SellPricePercentage = 0.5f;
	
	bool bShopMenuOpen = false;
	
private:
	void ModifyPlayerGold(float Amount);
	UInv_InventoryComponent* GetPlayerInventoryComponent() const;
	UAbilitySystemComponent* GetPlayerAbilitySystemComponent() const;
	
	void CreateShopWidget();
	void DestroyShopWidget();
	
	TWeakObjectPtr<AGAS_SlashHeroController> CurrentPlayerController;
};