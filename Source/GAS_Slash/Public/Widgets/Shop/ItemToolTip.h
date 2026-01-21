// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemToolTip.generated.h"

class UPA_ShopItem;
class UImage;
class UTextBlock;

UCLASS()
class GAS_SLASH_API UItemToolTip : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetItem(const UPA_ShopItem* Item);
	void SetPrice(float NewPrice);
	
private:
	UPROPERTY(meta = (BindWidget))
	UImage* IconImage;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemTitleText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemDescriptionText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemPriceText;
};