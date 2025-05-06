// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "SlashTypes/SlashStructTypes.h"
#include "DataAsset_HeroStartUpData.generated.h"


UCLASS()
class GAS_SLASH_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual	void GiveToAbilitySystemComponent(UGAS_SlashAbilitySystemComponent* InASCToGive, int32 ApplyLevel) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FSlashHeroAbilitySet> HeroStartUpAbilitySets;
	
};
