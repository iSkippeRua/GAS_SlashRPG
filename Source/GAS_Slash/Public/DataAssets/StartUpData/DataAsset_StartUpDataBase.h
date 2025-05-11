// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UGAS_SlashAbilitySystemComponent;
class UGAS_SlashGameplayAbility;
class UGameplayEffect;

UCLASS()
class GAS_SLASH_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UGAS_SlashAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
	
protected:
	void GrantAbilities(TArray<TSubclassOf<UGAS_SlashGameplayAbility>>& InAbilitiesToGive, UGAS_SlashAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
	
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UGAS_SlashGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UGAS_SlashGameplayAbility>> ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UGameplayEffect>> StartUpGameplayEffects;
};
