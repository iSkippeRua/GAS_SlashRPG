// Dmytro Chesniuk All Rights Reserved


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "AbilitySystem/Abilities/GAS_SlashGameplayAbility.h"
#include "AbilitySystem/GAS_SlashAbilitySystemComponent.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UGAS_SlashAbilitySystemComponent* InASCToGive,
                                                              int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);	
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);	
}

void UDataAsset_StartUpDataBase::GrantAbilities(TArray<TSubclassOf<UGAS_SlashGameplayAbility>>& InAbilitiesToGive,
	UGAS_SlashAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if(InAbilitiesToGive.IsEmpty()) return;

	for(const TSubclassOf<UGAS_SlashGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if(!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
