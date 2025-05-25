// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GAS_SlashGameplayAbility.h"
#include "GAS_SlashEnemyGameplayAbility.generated.h"

class AGAS_SlashEnemyCharacter;
class UEnemyCombatComponent;

UCLASS()
class GAS_SLASH_API UGAS_SlashEnemyGameplayAbility : public UGAS_SlashGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "GAS_Slash|Ability")
	AGAS_SlashEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "GAS_Slash|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "GAS_Slash|Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat);

private:
	TWeakObjectPtr<AGAS_SlashEnemyCharacter> CachedEnemyCharacter;
};
