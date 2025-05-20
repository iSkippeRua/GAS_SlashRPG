// Dmytro Chesniuk All Rights Reserved


#include "Widgets/SlashWidgetBase.h"
#include "Interfaces/PawnUIInterface.h"

void USlashWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if(UHeroUIComponent* HeroUIComponent = PawnUIInterface->GetHeroUIComponent())
		{
			BP_OnOwningHeroUIComponentInitialized(HeroUIComponent);
		}
	}
}

void USlashWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if(IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(OwningEnemyActor))
	{
		UEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent();

		checkf(EnemyUIComponent, TEXT("Failed to extrac an EnemyUIComponent from %s"), *OwningEnemyActor->GetActorNameOrLabel());

		BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
	}
}
