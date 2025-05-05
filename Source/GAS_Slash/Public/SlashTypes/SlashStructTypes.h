// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "SlashStructTypes.generated.h"

class UGAS_SlashHeroLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FGAS_SlashHeroWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGAS_SlashHeroLinkedAnimLayer> WeaponAnimLayerToLink;
};