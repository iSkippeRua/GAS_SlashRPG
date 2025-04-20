// Dmytro Chesniuk All Rights Reserved


#include "Characters/GAS_SlashBaseCharacter.h"

AGAS_SlashBaseCharacter::AGAS_SlashBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

}