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

UHeroUIComponent* UGAS_SlashHeroGameplayAbility::GetHeroUIComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroUIComponent();
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

bool UGAS_SlashHeroGameplayAbility::GetAbilityRemainingCooldownByTag(FGameplayTag InCooldownTag,
	float& TotalCooldownTime, float& RemainingCooldownTime)
{
	check(InCooldownTag.IsValid());

	FGameplayEffectQuery CooldownQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(InCooldownTag.GetSingleTagContainer());
	
	TArray<TPair<float, float>> TimeRemainingAndDuration = GetAbilitySystemComponentFromActorInfo()->GetActiveEffectsTimeRemainingAndDuration(CooldownQuery);

	if(!TimeRemainingAndDuration.IsEmpty())
	{
		RemainingCooldownTime = TimeRemainingAndDuration[0].Key;
		TotalCooldownTime = TimeRemainingAndDuration[0].Value;
	}

	return RemainingCooldownTime > 0.f;
}
