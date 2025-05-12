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

	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

protected:
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

private:
	void InitEnemyStartUpData();

public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
