// Dmytro Chesniuk All Rights Reserved


#include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"
#include "AbilitySystem/GAS_SlashAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/GAS_SlashEnemyGameplayAbility.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UGAS_SlashAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	if(!EnemyCombatAbilities.IsEmpty())
	{
		for(const TSubclassOf<UGAS_SlashEnemyGameplayAbility>& AbilityClass : EnemyCombatAbilities)
		{
			if(!AbilityClass) continue;

			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;
			
			InASCToGive->GiveAbility(AbilitySpec);
		}
	}
}
