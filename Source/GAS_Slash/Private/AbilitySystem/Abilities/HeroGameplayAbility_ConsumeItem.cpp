// Dmytro Chesniuk All Rights Reserved

#include "AbilitySystem/Abilities/HeroGameplayAbility_ConsumeItem.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/GAS_SlashAbilitySystemComponent.h"

void UHeroGameplayAbility_ConsumeItem::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UHeroGameplayAbility_ConsumeItem::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UHeroGameplayAbility_ConsumeItem::ConsumeItem()
{
	check(HealingGameplayEffectClass);

	UGameplayEffect* EffectCDO = HealingGameplayEffectClass->GetDefaultObject<UGameplayEffect>();

	UGAS_SlashAbilitySystemComponent* AbilitySystemComponent = GetSlashAbilitySystemComponentFromActorInfo();
	
	AbilitySystemComponent->ApplyGameplayEffectToSelf(
		EffectCDO,
		GetAbilityLevel(),
		AbilitySystemComponent->MakeEffectContext()
	);
}
