// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Components/Inv_ItemComponent.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Player/Inv_PlayerController.h"

UInv_ItemComponent::UInv_ItemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	PickUpMessage = FString("Press E - Pick Up");

	SetIsReplicatedByDefault(true);
	
	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Detection Sphere"));
	DetectionSphere->SetSphereRadius(DetectionSphereRadius);
	DetectionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DetectionSphere->SetCollisionObjectType(ECC_WorldDynamic);
	DetectionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	DetectionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void UInv_ItemComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (DetectionSphere && GetOwner())
	{
		DetectionSphere->AttachToComponent(
			GetOwner()->GetRootComponent(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale
		);
		
		DetectionSphere->RegisterComponent();
		
		DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereBeginOverlap);
		DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnSphereEndOverlap);
	}
}

void UInv_ItemComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, ItemManifest);
}

void UInv_ItemComponent::InitItemManifest(FInv_ItemManifest CopyOfManifest)
{
	ItemManifest = CopyOfManifest;
}

void UInv_ItemComponent::OnPickedUp()
{
	GetOwner()->Destroy();
}

void UInv_ItemComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor))
		return;
	
	ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
	if (!PlayerCharacter)
		return;
	
	AInv_PlayerController* PlayerController = Cast<AInv_PlayerController>(PlayerCharacter->GetController());
	if (PlayerController)
	{
		PlayerController->OnItemDetectionSphereBeginOverlap(GetOwner());
	}
}

void UInv_ItemComponent::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsValid(OtherActor))
		return;
	
	ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
	if (!PlayerCharacter)
		return;
	
	AInv_PlayerController* PlayerController = Cast<AInv_PlayerController>(PlayerCharacter->GetController());
	if (PlayerController)
	{
		PlayerController->OnItemDetectionSphereEndOverlap(GetOwner());
	}
}
