// Dmytro Chesniuk All Rights Reserved


#include "Components/UI/EnemyUIComponent.h"

#include "Widgets/SlashWidgetBase.h"

void UEnemyUIComponent::RegisterEnemyDrawnWidget(USlashWidgetBase* InWidgetToRegister)
{
	EnemyDrawnWidgets.Add(InWidgetToRegister);
}

void UEnemyUIComponent::RemoveEnemyDrawnWidgetIfAny()
{
	if(EnemyDrawnWidgets.IsEmpty()) return;

	for(USlashWidgetBase* DrawnWidget : EnemyDrawnWidgets)
	{
		if(DrawnWidget)
		{
			DrawnWidget->RemoveFromParent();
		}
	}

	EnemyDrawnWidgets.Empty();
}
