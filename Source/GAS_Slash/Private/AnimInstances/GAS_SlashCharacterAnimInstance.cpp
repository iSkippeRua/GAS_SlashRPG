// Dmytro Chesniuk All Rights Reserved


#include "AnimInstances/GAS_SlashCharacterAnimInstance.h"
#include "Characters/GAS_SlashBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UGAS_SlashCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AGAS_SlashBaseCharacter>(TryGetPawnOwner());
	
	if(OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UGAS_SlashCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if(!OwningCharacter || !OwningMovementComponent) return;

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D()>0.f;
}
