// Dmytro Chesniuk All Rights Reserved


#include "Characters/GAS_SlashBaseCharacter.h"
#include "AbilitySystem/GAS_SlashAbilitySystemComponent.h"
#include "AbilitySystem/GAS_SlashAttributeSet.h"

AGAS_SlashBaseCharacter::AGAS_SlashBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	SlashAbilitySystemComponent = CreateDefaultSubobject<UGAS_SlashAbilitySystemComponent>(TEXT("SlashAbilitySystemComponent"));
	SlashAttributeSet = CreateDefaultSubobject<UGAS_SlashAttributeSet>(TEXT("SlashAttributeSet"));
}

UAbilitySystemComponent* AGAS_SlashBaseCharacter::GetAbilitySystemComponent() const
{
	return GetSlashAbilitySystemComponent();
}

void AGAS_SlashBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(SlashAbilitySystemComponent)
	{
		SlashAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}
