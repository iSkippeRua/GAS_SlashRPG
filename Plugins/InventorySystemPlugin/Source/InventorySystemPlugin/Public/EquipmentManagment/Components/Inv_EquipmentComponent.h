// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Inv_EquipmentComponent.generated.h"

struct FGameplayTag;
struct FInv_ItemManifest;
struct FInv_EquipmentFragment;
class AInv_EquipActor;
class UInv_InventoryItem;
class UInv_InventoryComponent;
class APlayerController;
class USkeletalMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemEquipped, FGameplayTag, EquippedItemType, FGameplayTag, EquippedItemSlot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemUnequipped, FGameplayTag, UnequippedItemType, FGameplayTag, UnequippedItemSlot);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORYSYSTEMPLUGIN_API UInv_EquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void SetOwningSkeletalMesh(USkeletalMeshComponent* OwningMesh);

	void SetIsProxy(bool bProxy) { bIsProxy = bProxy; }

	void InitializeOwner(APlayerController* PlayerController);

	FOnItemEquipped OnItemEquippedSignal;
	FOnItemUnequipped OnItemUnequippedSignal;
	
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnItemEquipped(UInv_InventoryItem* EquippedItem);

	UFUNCTION()
	void OnItemUnequipped(UInv_InventoryItem* UnequippedItem);

	void InitInventoryComponent();
	
	void InitPlayerController();

	AInv_EquipActor* FindEquippedActorByTag(const FGameplayTag& EquipmentTypeTag);

	void RemoveEquippedActor(const FGameplayTag& EquipmentTypeTag);

	UFUNCTION()
	void OnPossessedPawnChange(APawn* OldPawn, APawn* NewPawn);

	AInv_EquipActor* SpawnEquippedActor(FInv_EquipmentFragment* EquipmentFragment, const FInv_ItemManifest& Manifest, USkeletalMeshComponent* AttachMesh);
	
	TWeakObjectPtr<UInv_InventoryComponent> InventoryComponent;

	TWeakObjectPtr<APlayerController> OwningPlayerController;

	TWeakObjectPtr<USkeletalMeshComponent> OwnerSkeletalMesh;

	UPROPERTY()
	TArray<TObjectPtr<AInv_EquipActor>> EquippedActors;

	bool bIsProxy{false};
	
};
