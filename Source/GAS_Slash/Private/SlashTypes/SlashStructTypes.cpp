// Dmytro Chesniuk All Rights Reserved


#include "SlashTypes/SlashStructTypes.h"
#include "AbilitySystem/Abilities/GAS_SlashHeroGameplayAbility.h"

bool FSlashHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
