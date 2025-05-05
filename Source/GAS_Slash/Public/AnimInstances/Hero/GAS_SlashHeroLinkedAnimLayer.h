// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/GAS_SlashBaseAnimInstance.h"
#include "GAS_SlashHeroLinkedAnimLayer.generated.h"

class UGAS_SlashHeroAnimInstance;

UCLASS()
class GAS_SLASH_API UGAS_SlashHeroLinkedAnimLayer : public UGAS_SlashBaseAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UGAS_SlashHeroAnimInstance* GetHeroAnimInstance() const;
};
