// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"

class AGAS_SlashHeroWeapon;

UCLASS()
class GAS_SLASH_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GAS_Slash|Combat")
	AGAS_SlashHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
};
