// Dmytro Chesniuk All Rights Reserved


#include "AbilitySystem/GAS_SlashAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/GAS_SlashHeroGameplayAbility.h"
#include "GAS_SlashGameplayTags.h"

void UGAS_SlashAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if(!InInputTag.IsValid()) return;

	for(const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if(!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag)) continue;

		if(InInputTag.MatchesTag(GAS_SlashGameplayTags::InputTag_Toggleable) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		} else
		{
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UGAS_SlashAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if(!InInputTag.IsValid() || !InInputTag.MatchesTag(GAS_SlashGameplayTags::InputTag_MustBeHeld)) return;

	for(const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if(AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
	}
}

void UGAS_SlashAbilitySystemComponent::GrantHeroWeaponAbilities(
	const TArray<FSlashHeroAbilitySet>& InDefaultWeaponAbilities, const TArray<FSlashHeroSpecialAbilitySet>& InSpecialWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
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

	for(const FSlashHeroSpecialAbilitySet& AbilitySet : InSpecialWeaponAbilities)
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

bool UGAS_SlashAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{
	check(AbilityTagToActivate.IsValid());

	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(), FoundAbilitySpecs);

	if(!FoundAbilitySpecs.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, FoundAbilitySpecs.Num() - 1);
		FGameplayAbilitySpec* SpecToActivate = FoundAbilitySpecs[RandomAbilityIndex];

		check(SpecToActivate);

		if(!SpecToActivate->IsActive())
		{
			return TryActivateAbility(SpecToActivate->Handle);
		}
	}

	return false;
}
