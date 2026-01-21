// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

class UItemToolTip;
class UImage;

UCLASS()
class GAS_SLASH_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void SetIcon(UTexture2D* IconTexture);
	
private:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	virtual void RightMouseButtonClicked();
	virtual void LeftMouseButtonClicked();
	
	UPROPERTY(meta = (BindWidget))
	UImage* ItemIcon;
};