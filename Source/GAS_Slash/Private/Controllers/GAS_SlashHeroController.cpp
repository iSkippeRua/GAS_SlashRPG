// Dmytro Chesniuk All Rights Reserved


#include "Controllers/GAS_SlashHeroController.h"

#include "GameFramework/Character.h"

AGAS_SlashHeroController::AGAS_SlashHeroController()
{
    HeroTeamID = FGenericTeamId(0);
    
    // Create the equipment component
    EquipmentComponent = CreateDefaultSubobject<UInv_EquipmentComponent>(TEXT("EquipmentComponent"));
}

void AGAS_SlashHeroController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    
    // Initialize equipment component when possessing a pawn
    if (ACharacter* OwningCharacter = Cast<ACharacter>(InPawn))
    {
        if (EquipmentComponent)
        {
            EquipmentComponent->SetOwningSkeletalMesh(OwningCharacter->GetMesh());
            EquipmentComponent->InitializeOwner(this);
        }
    }
}

FGenericTeamId AGAS_SlashHeroController::GetGenericTeamId() const
{
	return HeroTeamID;
}

void AGAS_SlashHeroController::BeginPlay()
{
	Super::BeginPlay();
}

void AGAS_SlashHeroController::SetupInputComponent()
{
	Super::SetupInputComponent();
}