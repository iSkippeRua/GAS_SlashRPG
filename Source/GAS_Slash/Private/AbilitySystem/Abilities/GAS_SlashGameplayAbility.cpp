// Dmytro Chesniuk All Rights Reserved


#include "AbilitySystem/Abilities/GAS_SlashGameplayAbility.h"
#include "AbilitySystem/GAS_SlashAbilitySystemComponent.h"

void UGAS_SlashGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if(AbilityActivationPolicy == EGAS_SlashAbilityActivationPolicy::OnGiven)
	{
		if(ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UGAS_SlashGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if(AbilityActivationPolicy == EGAS_SlashAbilityActivationPolicy::OnGiven)
	{
		if(ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}
