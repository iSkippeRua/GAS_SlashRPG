#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GAS_SlashShopWidget.generated.h"

class UGAS_SlashShopComponent;
class UGAS_SlashShopItemData;
class UListView;
class UTextBlock;
class UButton;

UCLASS()
class GAS_SLASH_API UGAS_SlashShopWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void PopulateShopItems(const TArray<UGAS_SlashShopItemData*>& ShopItems);
	
	void SetShopComponent(UGAS_SlashShopComponent* InShopComponent);
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	void UpdateGoldDisplay();

protected:
	UFUNCTION()
	void OnItemPurchasedHandler(UGAS_SlashShopItemData* ShopItem, int32 Quantity);
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	void OnCloseButtonClicked();
	
	UPROPERTY(meta=(BindWidget))
	UListView* ShopItemListView;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* GoldAmountText;
	
	UPROPERTY(meta=(BindWidget))
	UButton* CloseButton;
	
	UPROPERTY()
	TObjectPtr<UGAS_SlashShopComponent> ShopComponent;
};