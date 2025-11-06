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
	UGAS_SlashAbilitySystemComponent* AbilitySystemComponent = GetSlashAbilitySystemComponentFromActorInfo();
	if (!AbilitySystemComponent)
	{
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
		return;
	}

	FGameplayTag ConsumedItemTag = AbilitySystemComponent->GetLastConsumedItemTag();

	const TSubclassOf<UGameplayEffect>* FoundEffect = ItemEffectMap.Find(ConsumedItemTag);
	if (!FoundEffect)
	{
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
		return;
	}

	UGameplayEffect* EffectCDO = (*FoundEffect)->GetDefaultObject<UGameplayEffect>();
	
	AbilitySystemComponent->ApplyGameplayEffectToSelf(
		EffectCDO,
		GetAbilityLevel(),
		AbilitySystemComponent->MakeEffectContext()
	);
	
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}