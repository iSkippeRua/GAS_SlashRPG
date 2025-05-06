// Dmytro Chesniuk All Rights Reserved


#include "Items/Weapons/GAS_SlashHeroWeapon.h"

void AGAS_SlashHeroWeapon::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	GrantedAbilitySpecHandles = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> AGAS_SlashHeroWeapon::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}
