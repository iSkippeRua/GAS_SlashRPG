// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/Inv_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Widgets/HUD/Inv_HUDWidget.h"
#include "InputMappingContext.h"
#include "Interaction/Inv_Highlight.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"
#include "Items/Components/Inv_ItemComponent.h"
#include "Kismet/GameplayStatics.h"

AInv_PlayerController::AInv_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	TraceLength = 500.f;
	ItemTraceChannel = ECC_GameTraceChannel1;
}

void AInv_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TraceForItem();
}

void AInv_PlayerController::ToggleInventory()
{
	if (!InventoryComponent.IsValid())
		return;

	InventoryComponent->ToggleInventoryMenu();

	if (InventoryComponent->IsMenuOpen())
	{
		HUDWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		HUDWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void AInv_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	if (IsValid(Subsystem))
	{
		for (UInputMappingContext* CurrentContext : DefaultIMC)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}

	InventoryComponent = FindComponentByClass<UInv_InventoryComponent>();

	CreateHUDWidget();
}

void AInv_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(PrimaryInteractAction, ETriggerEvent::Started, this, &ThisClass::PrimaryInteract);
	EnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Started, this, &ThisClass::ToggleInventory);
}

void AInv_PlayerController::PrimaryInteract()
{
	if (!CurrentActor.IsValid())
		return;

	UInv_ItemComponent* ItemComponent = CurrentActor->FindComponentByClass<UInv_ItemComponent>();
	
	if (!IsValid(ItemComponent) || !InventoryComponent.IsValid())
		return;

	InventoryComponent->TryAddItem(ItemComponent);
}

void AInv_PlayerController::CreateHUDWidget()
{
	if (!IsLocalController())
		return;

	HUDWidget = CreateWidget<UInv_HUDWidget>(this, HUDWidgetClass);
	
	if (IsValid(HUDWidget))
	{
		HUDWidget->AddToViewport();
	}
}

void AInv_PlayerController::TraceForItem()
{
	if (!IsValid(GEngine) || !IsValid(GEngine->GameViewport))
		return;
	
	FVector2D ViewportSize;
	
	GEngine->GameViewport->GetViewportSize(ViewportSize);

	const FVector2D ViewportCenter = ViewportSize / 2.f;

	FVector TraceStart;
	FVector Forward;

	if (!UGameplayStatics::DeprojectScreenToWorld(this, ViewportCenter, TraceStart, Forward))
		return;

	const FVector TraceEnd = TraceStart + Forward * TraceLength;
	FHitResult HitResult;

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ItemTraceChannel);

	LastActor = CurrentActor;
	CurrentActor = HitResult.GetActor();

	if (!CurrentActor.IsValid())
	{
		if (IsValid(HUDWidget)) HUDWidget->HidePickUpMessage();
	}

	if (CurrentActor == LastActor)
		return;

	if (CurrentActor.IsValid())
	{
		if (UActorComponent* Highlight = CurrentActor->FindComponentByInterface(UInv_Highlight::StaticClass()); IsValid(Highlight))
		{
			IInv_Highlight::Execute_Highlight(Highlight);
		}
		
		UInv_ItemComponent* ItemComponent = CurrentActor->FindComponentByClass<UInv_ItemComponent>();
		
		if (!IsValid(ItemComponent))
			return;

		if (IsValid(HUDWidget))
		{
			HUDWidget->ShowPickUpMessage(ItemComponent->GetPickUpMessage());
		}
	}

	if (LastActor.IsValid())
	{
		if (UActorComponent* Highlight = LastActor->FindComponentByInterface(UInv_Highlight::StaticClass()); IsValid(Highlight))
		{
			IInv_Highlight::Execute_UnHighlight(Highlight);
		}
	}
}
