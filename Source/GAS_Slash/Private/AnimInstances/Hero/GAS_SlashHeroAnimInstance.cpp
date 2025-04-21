// Dmytro Chesniuk All Rights Reserved


#include "AnimInstances/Hero/GAS_SlashHeroAnimInstance.h"
#include "Characters/GAS_SlashHeroCharacter.h"

void UGAS_SlashHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if(OwningCharacter)
	{
		OwningHeroCharacter = Cast<AGAS_SlashHeroCharacter>(OwningCharacter);
	}
}

void UGAS_SlashHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if(bHasAcceleration)
	{
		IdleElapsedTime = 0.f;
		bShouldEnterRelaxState = false;
	} else
	{
		IdleElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = (IdleElapsedTime >= EnterRelaxStateThreshold);
	}
}
