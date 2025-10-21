// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GAS_SlashHeroGameplayAbility.h"
#include "HeroGameplayAbility_ConsumeItem.generated.h"

UCLASS()
class GAS_SLASH_API UHeroGameplayAbility_ConsumeItem : public UGAS_SlashHeroGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintCallable)
	void ConsumeItem();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> HealingGameplayEffectClass;
};
