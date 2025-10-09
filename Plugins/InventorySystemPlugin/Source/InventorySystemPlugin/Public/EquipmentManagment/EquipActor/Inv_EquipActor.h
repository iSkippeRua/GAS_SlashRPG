// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "Inv_EquipActor.generated.h"

UCLASS()
class INVENTORYSYSTEMPLUGIN_API AInv_EquipActor : public AActor
{
	GENERATED_BODY()

public:
	AInv_EquipActor();

	FGameplayTag GetEquipmentType () const { return EquipmentType; }
	void SetEquipmentType(FGameplayTag InEquipmentType) { EquipmentType = InEquipmentType; }

private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FGameplayTag EquipmentType;

};
