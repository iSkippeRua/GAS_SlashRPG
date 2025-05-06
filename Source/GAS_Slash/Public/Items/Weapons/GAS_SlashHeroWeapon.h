// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/GAS_SlashWeaponBase.h"
#include "SlashTypes/SlashStructTypes.h"
#include "GameplayAbilitySpecHandle.h"
#include "GAS_SlashHeroWeapon.generated.h"

UCLASS()
class GAS_SLASH_API AGAS_SlashHeroWeapon : public AGAS_SlashWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FGAS_SlashHeroWeaponData HeroWeaponData;

	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;
	
private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
