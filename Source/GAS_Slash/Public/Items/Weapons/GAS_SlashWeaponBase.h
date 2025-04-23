// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GAS_SlashWeaponBase.generated.h"

class UBoxComponent;

UCLASS()
class GAS_SLASH_API AGAS_SlashWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AGAS_SlashWeaponBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapons")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapons")
	UBoxComponent* WeaponCollisionBox;

public:
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }
	
};
