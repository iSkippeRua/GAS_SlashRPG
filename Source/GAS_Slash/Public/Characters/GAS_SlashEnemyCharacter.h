// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/GAS_SlashBaseCharacter.h"
#include "GAS_SlashEnemyCharacter.generated.h"

class UEnemyCombatComponent;

UCLASS()
class GAS_SLASH_API AGAS_SlashEnemyCharacter : public AGAS_SlashBaseCharacter
{
	GENERATED_BODY()

public:
	AGAS_SlashEnemyCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

public:
		FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
