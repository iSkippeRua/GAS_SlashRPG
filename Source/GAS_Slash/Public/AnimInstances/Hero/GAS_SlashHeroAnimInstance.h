// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/GAS_SlashCharacterAnimInstance.h"
#include "GAS_SlashHeroAnimInstance.generated.h"


class AGAS_SlashHeroCharacter;

UCLASS()
class GAS_SLASH_API UGAS_SlashHeroAnimInstance : public UGAS_SlashCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|References")
	AGAS_SlashHeroCharacter* OwningHeroCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AnimData|LocomotionData")
	float EnterRelaxStateThreshold = 5.f;
	
	float IdleElapsedTime;
};
