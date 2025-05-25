// Dmytro Chesniuk All Rights Reserved


#include "AnimInstances/GAS_SlashBaseAnimInstance.h"
#include "SlashFunctionLibrary.h"

bool UGAS_SlashBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if(APawn* OwningPawn = TryGetPawnOwner())
	{
		return USlashFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}

	return false;
}
