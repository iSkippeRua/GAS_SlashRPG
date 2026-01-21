// Dmytro Chesniuk All Rights Reserved

#include "Widgets/Shop/ItemWidget.h"
#include "Components/Image.h"
#include "Widgets/Shop/ItemToolTip.h"

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetIsFocusable(true);
}

void UItemWidget::SetIcon(UTexture2D* IconTexture)
{
	if (ItemIcon && IsValid(IconTexture))
	{
		ItemIcon->SetBrushFromTexture(IconTexture);
	}
}

FReply UItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply SuperReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		return FReply::Handled().SetUserFocus(TakeWidget());
	}
	
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return FReply::Handled().SetUserFocus(TakeWidget());
	}
	
	return SuperReply;
}

FReply UItemWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply SuperReply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
	
	if (HasAnyUserFocus())
	{
		if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
		{
			RightMouseButtonClicked();
			return FReply::Handled();
		}
		
		if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		{
			LeftMouseButtonClicked();
			return FReply::Handled();
		}
	}
	
	return SuperReply;
}

void UItemWidget::RightMouseButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Right Mouse Button clicked."));
}

void UItemWidget::LeftMouseButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Left Mouse Button clicked."))
}
