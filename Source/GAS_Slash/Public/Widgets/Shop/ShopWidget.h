// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidget.generated.h"

class UTileView;
class UPA_ShopItem;
class UShopItemWidget;
class UShop_InteractionComponent;
class AGAS_SlashHeroController;

UCLASS()
class GAS_SLASH_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	void InitializeWithShop(UShop_InteractionComponent* InShopInteractionComponent, AGAS_SlashHeroController* InPlayerController);
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	void OnShopMenuToggled(bool bOpen);

	UFUNCTION(BlueprintCallable, Category = "Shop")
	AGAS_SlashHeroController* GetPlayerController() const { return PlayerController; }
	
private:
	void LoadShopItems();
	void ShopItemLoadFinished();
	void ShopItemWidgetGenerated(UUserWidget& NewWidget);
	
	UPROPERTY(meta = (BindWidget))
	UTileView* ShopItemList;
	
	UPROPERTY()
	TMap<const UPA_ShopItem*, const UShopItemWidget*> ItemsMap;
	
	UPROPERTY()
	UShop_InteractionComponent* ShopInteractionComponent;
	
	UPROPERTY()
	AGAS_SlashHeroController* PlayerController;
};