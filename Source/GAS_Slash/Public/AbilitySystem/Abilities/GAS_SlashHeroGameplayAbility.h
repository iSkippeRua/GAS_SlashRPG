// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GAS_SlashGameplayAbility.h"
#include "GAS_SlashHeroGameplayAbility.generated.h"

class AGAS_SlashHeroCharacter;
class AGAS_SlashHeroController;
class UHeroCombatComponent;

UCLASS()
class GAS_SLASH_API UGAS_SlashHeroGameplayAbility : public UGAS_SlashGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "GAS_Slash|Ability")
	AGAS_SlashHeroCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "GAS_Slash|Ability")
	AGAS_SlashHeroController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "GAS_Slash|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "GAS_Slash|Ability")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);

	UFUNCTION(BlueprintCallable, Category = "GAS_Slash|Ability")
	bool GetAbilityRemainingCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemainingCooldownTime);
	
	
private:
	TWeakObjectPtr<AGAS_SlashHeroCharacter> CachedSlashHeroCharacter;
	TWeakObjectPtr<AGAS_SlashHeroController> CachedSlashHeroController;
};
