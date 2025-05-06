// Dmytro Chesniuk All Rights Reserved


#include "AbilitySystem/GAS_SlashAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/GAS_SlashGameplayAbility.h"

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

void UGAS_SlashAbilitySystemComponent::GrantHeroWeaponAbilities(
	const TArray<FSlashHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if(InDefaultWeaponAbilities.IsEmpty()) return;

	for(const FSlashHeroAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		if(!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);
		
		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UGAS_SlashAbilitySystemComponent::RemoveGrantedHeroWeaponAbilities(UPARAM(ref)TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if(InSpecHandlesToRemove.IsEmpty()) return;

	for(const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
	{
		if(SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);
		}
	}

	InSpecHandlesToRemove.Empty();
}
