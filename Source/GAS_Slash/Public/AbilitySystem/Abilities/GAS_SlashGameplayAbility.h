// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
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
	
	UPROPERTY(EditDefaultsOnly, Category="GAS_Slash|Ability")
	EGAS_SlashAbilityActivationPolicy AbilityActivationPolicy = EGAS_SlashAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "GAS_Slash|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "GAS_Slash|Ability")
	UGAS_SlashAbilitySystemComponent* GetSlashAbilitySystemComponentFromActorInfo() const;
};
