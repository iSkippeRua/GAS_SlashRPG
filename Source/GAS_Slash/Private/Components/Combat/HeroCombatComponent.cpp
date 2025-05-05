// Dmytro Chesniuk All Rights Reserved


#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/GAS_SlashHeroWeapon.h"

AGAS_SlashHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AGAS_SlashHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}
