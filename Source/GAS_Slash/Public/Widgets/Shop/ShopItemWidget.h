// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Shop/ItemWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ShopItemWidget.generated.h"

class UPA_ShopItem;
class UShopItemWidget;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemPurchaseIssued, const UPA_ShopItem*, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnShopItemClicked, const UShopItemWidget*);

UCLASS()
class GAS_SLASH_API UShopItemWidget : public UItemWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	FORCEINLINE const UPA_ShopItem* GetShopItem() const { return ShopItem; }
	
	FOnItemPurchaseIssued OnItemPurchaseIssued;
	FOnShopItemClicked OnShopItemClicked;
	
private:
	virtual void RightMouseButtonClicked() override;
	//virtual void LeftMouseButtonClicked() override;
	
	UPROPERTY()
	const UPA_ShopItem* ShopItem;
};