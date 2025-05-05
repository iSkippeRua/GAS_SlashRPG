// Dmytro Chesniuk All Rights Reserved


#include "AbilitySystem/GAS_SlashAbilitySystemComponent.h"

void UGAS_SlashAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if(!InInputTag.IsValid()) return;

	for(const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if(!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag)) continue;

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UGAS_SlashAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
}
