// Dmytro Chesniuk All Rights Reserved

#include "AbilitySystem/Abilities/GAS_SlashHeroGameplayAbility.h"
#include "Characters/GAS_SlashHeroCharacter.h"
#include "Controllers/GAS_SlashHeroController.h"

AGAS_SlashHeroCharacter* UGAS_SlashHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if(!CachedSlashHeroCharacter.IsValid())
	{
		CachedSlashHeroCharacter = Cast<AGAS_SlashHeroCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedSlashHeroCharacter.IsValid() ? CachedSlashHeroCharacter.Get() : nullptr;
}

AGAS_SlashHeroController* UGAS_SlashHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if(!CachedSlashHeroController.IsValid())
	{
		CachedSlashHeroController = Cast<AGAS_SlashHeroController>(CurrentActorInfo->PlayerController);
	}

	return CachedSlashHeroController.IsValid() ? CachedSlashHeroController.Get() : nullptr;
}

UHeroCombatComponent* UGAS_SlashHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}
