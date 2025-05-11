// Dmytro Chesniuk All Rights Reserved


#include "AbilitySystem/Abilities/GAS_SlashEnemyGameplayAbility.h"
#include "Characters/GAS_SlashEnemyCharacter.h"

AGAS_SlashEnemyCharacter* UGAS_SlashEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if(!CachedEnemyCharacter.IsValid())
	{
		CachedEnemyCharacter = Cast<AGAS_SlashEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedEnemyCharacter.IsValid() ? CachedEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UGAS_SlashEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
