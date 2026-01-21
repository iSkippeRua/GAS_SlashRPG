// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "Player/Inv_PlayerController.h"
#include "EquipmentManagment/Components/Inv_EquipmentComponent.h"
#include "GAS_SlashHeroController.generated.h"

class UShop_InteractionComponent;

UCLASS()
class GAS_SLASH_API AGAS_SlashHeroController : public AInv_PlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AGAS_SlashHeroController();
	
	virtual FGenericTeamId GetGenericTeamId() const override;
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	void SetCurrentShop(UShop_InteractionComponent* ShopInteractionComponent);
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	UShop_InteractionComponent* GetCurrentShop() const { return CurrentShopInteractionComponent; }

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
    virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void HandleItemConsumed(FGameplayTag ConsumedItemTag);

	UFUNCTION()
	void HandleItemEquipped(FGameplayTag EquippedItemType, FGameplayTag EquippedItemSlot);

	UFUNCTION()
	void HandleItemUnequipped(FGameplayTag UnequippedItemType, FGameplayTag UnequippedItemSlot);
    
private:
	FGenericTeamId HeroTeamID;
    
    UPROPERTY(VisibleAnywhere)
    UInv_EquipmentComponent* EquipmentComponent;

	UPROPERTY()
	UInv_InventoryComponent* InventoryComponent;
	
	UPROPERTY()
	UShop_InteractionComponent* CurrentShopInteractionComponent;
};