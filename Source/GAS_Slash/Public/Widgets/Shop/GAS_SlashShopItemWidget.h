#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "GAS_SlashShopItemWidget.generated.h"

class UGAS_SlashShopComponent;
class UGAS_SlashShopItemData;
class UImage;
class UTextBlock;
class UButton;

UCLASS()
class GAS_SLASH_API UGAS_SlashShopItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
protected:
	UFUNCTION()
	void OnPurchaseButtonClicked();
	
	void UpdateDisplay();
	UGAS_SlashShopComponent* GetShopComponent() const;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> ItemIcon;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ItemNameText;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ItemDescriptionText;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> PriceText;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ItemStockText;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> PurchaseButton;
	
	UPROPERTY()
	UGAS_SlashShopItemData* ShopItemData;
};