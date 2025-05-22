// Dmytro Chesniuk All Rights Reserved


#include "Controllers/GAS_SlashHeroController.h"

AGAS_SlashHeroController::AGAS_SlashHeroController()
{
	HeroTeamID = FGenericTeamId(0);
}

FGenericTeamId AGAS_SlashHeroController::GetGenericTeamId() const
{
	return HeroTeamID;
}
