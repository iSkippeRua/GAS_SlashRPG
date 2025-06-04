// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SlashTypes/SlashEnumTypes.h"
#include "GAS_SlashGameplayAbility.generated.h"

class UPawnCombatComponent;
class UGAS_SlashAbilitySystemComponent;

UENUM(BlueprintType)
enum class EGAS_SlashAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

UCLASS()
class GAS_SLASH_API UGAS_SlashGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual bool DoesAbilitySatisfyTagRequirements(const UAbilitySystemComponent& AbilitySystemComponent, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
	
	UPROPERTY(EditDefaultsOnly, Category="GAS_Slash|Ability")
	EGAS_SlashAbilityActivationPolicy AbilityActivationPolicy = EGAS_SlashAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "GAS_Slash|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "GAS_Slash|Ability")
	UGAS_SlashAbilitySystemComponent* GetSlashAbilitySystemComponentFromActorInfo() const;

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "GAS_Slash|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, ESlashSuccessTypes& OutSuccessType);
};
