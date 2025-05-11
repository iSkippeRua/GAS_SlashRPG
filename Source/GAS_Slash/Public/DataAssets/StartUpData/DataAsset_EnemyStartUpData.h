// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "DataAsset_EnemyStartUpData.generated.h"

class UGAS_SlashEnemyGameplayAbility;

UCLASS()
class GAS_SLASH_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UGAS_SlashAbilitySystemComponent* InASCToGive, int32 ApplyLevel) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UGAS_SlashEnemyGameplayAbility>> EnemyCombatAbilities;
};
