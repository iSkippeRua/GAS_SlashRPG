// Dmytro Chesniuk All Rights Reserved


#include "SlashTypes/SlashStructTypes.h"
#include "AbilitySystem/Abilities/GAS_SlashGameplayAbility.h"

bool FSlashHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
