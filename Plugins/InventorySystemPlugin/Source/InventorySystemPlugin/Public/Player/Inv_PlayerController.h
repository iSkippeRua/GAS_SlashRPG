// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Inv_PlayerController.generated.h"

class UInv_InventoryComponent;
class UInv_HUDWidget;
class UInputMappingContext;
class UInputAction;

UENUM()
enum class ETraceState : uint8
{
	ELineTracing,
	EOverlapping
};

UCLASS()
class INVENTORYSYSTEMPLUGIN_API AInv_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AInv_PlayerController();
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ToggleInventory();
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void OnItemDetectionSphereBeginOverlap(AActor* ItemActor);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void OnItemDetectionSphereEndOverlap(AActor* ItemActor);
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void PrimaryInteract();
	void CreateHUDWidget();
	void TraceForItem();
	void UpdateCurrentOverlappingItem();
	void SwapHighlight(AActor* OldActor, AActor* NewActor);

	TWeakObjectPtr<UInv_InventoryComponent> InventoryComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TArray<TObjectPtr<UInputMappingContext>> DefaultIMC;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UInputAction> PrimaryInteractAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UInputAction> ToggleInventoryAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<UInv_HUDWidget> HUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UInv_HUDWidget> HUDWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	double TraceLength;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TEnumAsByte<ECollisionChannel> ItemTraceChannel;

	TWeakObjectPtr<AActor> CurrentActor;
	TWeakObjectPtr<AActor> LastActor;
	
	UPROPERTY()
	TArray<TWeakObjectPtr<AActor>> OverlappingItems;
	
	UPROPERTY()
	ETraceState TraceState = ETraceState::ELineTracing;
};
