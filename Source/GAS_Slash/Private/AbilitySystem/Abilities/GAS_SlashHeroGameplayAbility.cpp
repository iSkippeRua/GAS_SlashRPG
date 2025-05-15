// Dmytro Chesniuk All Rights Reserved

#include "AbilitySystem/Abilities/GAS_SlashHeroGameplayAbility.h"
#include "Characters/GAS_SlashHeroCharacter.h"
#include "Controllers/GAS_SlashHeroController.h"
#include "AbilitySystem/GAS_SlashAbilitySystemComponent.h"
#include "GAS_SlashGameplayTags.h"

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

FGameplayEffectSpecHandle UGAS_SlashHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag,
	int32 InUsedComboCount)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetSlashAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	
	FGameplayEffectSpecHandle EffectSpecHandle = GetSlashAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		GAS_SlashGameplayTags::Shared_SetByCaller_BaseDamage,
		InWeaponBaseDamage
	);

	if(InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(
			InCurrentAttackTypeTag,
			InUsedComboCount
		);
	}

	return EffectSpecHandle;
}
