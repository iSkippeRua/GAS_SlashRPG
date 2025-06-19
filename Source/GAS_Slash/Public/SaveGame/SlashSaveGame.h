// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SlashTypes/SlashEnumTypes.h"
#include "SlashSaveGame.generated.h"

UCLASS()
class GAS_SLASH_API USlashSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	ESlashGameDifficulty SavedCurrentGameDifficulty;
};
