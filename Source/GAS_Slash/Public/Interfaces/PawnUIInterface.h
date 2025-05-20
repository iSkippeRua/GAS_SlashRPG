// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnUIInterface.generated.h"

class UEnemyUIComponent;
class UHeroUIComponent;
class UPawnUIComponent;

UINTERFACE(MinimalAPI)
class UPawnUIInterface : public UInterface
{
	GENERATED_BODY()
};


class GAS_SLASH_API IPawnUIInterface
{
	GENERATED_BODY()

public:
	virtual UPawnUIComponent* GetPawnUIComponent() const = 0;

	virtual UHeroUIComponent* GetHeroUIComponent() const;

	virtual UEnemyUIComponent* GetEnemyUIComponent() const;
};
