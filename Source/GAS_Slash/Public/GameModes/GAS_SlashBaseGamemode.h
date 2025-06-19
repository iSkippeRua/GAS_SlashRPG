// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SlashTypes/SlashEnumTypes.h"
#include "GAS_SlashBaseGamemode.generated.h"


UCLASS()
class GAS_SLASH_API AGAS_SlashBaseGamemode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGAS_SlashBaseGamemode();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Settings")
	ESlashGameDifficulty CurrentGameDifficulty;

public:
	FORCEINLINE ESlashGameDifficulty GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }
};
