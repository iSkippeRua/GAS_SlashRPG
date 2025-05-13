// Dmytro Chesniuk All Rights Reserved


#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/GAS_SlashHeroWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS_SlashGameplayTags.h"

AGAS_SlashHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AGAS_SlashHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if(OverlappedActors.Contains(HitActor)) return;

	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		GAS_SlashGameplayTags::Shared_Event_MeleeHit,
		Data
	);
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}
