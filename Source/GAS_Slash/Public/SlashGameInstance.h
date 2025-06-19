// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/GameInstance.h"
#include "SlashGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FSlashGameLevelSet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (Categories = "GameData.Level"))
	FGameplayTag LevelTag;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> Level;

	bool IsValid() const
	{
		return LevelTag.IsValid() && !Level.IsNull();
	}
	
};

UCLASS()
class GAS_SLASH_API USlashGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	
protected:
	virtual void OnPreLoadMap(const FString& MapName);
	virtual void OnDestinationWorldLoaded(UWorld* LoadedWorld);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FSlashGameLevelSet> GameLevelSets;

public:
	UFUNCTION(BlueprintPure, meta = (GameplayTagFilter = "GameData.Level"))
	TSoftObjectPtr<UWorld> GetGameLevelByTag(FGameplayTag InTag) const;
	
};

