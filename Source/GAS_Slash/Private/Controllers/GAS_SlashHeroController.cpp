// Dmytro Chesniuk All Rights Reserved


#include "Controllers/GAS_SlashHeroController.h"
#include "GAS_SlashGameplayTags.h"
#include "AbilitySystem/GAS_SlashAbilitySystemComponent.h"
#include "Characters/GAS_SlashHeroCharacter.h"
#include "GameFramework/Character.h"
#include "InventoryManagement/Components/Inv_InventoryComponent.h"

AGAS_SlashHeroController::AGAS_SlashHeroController()
{
    HeroTeamID = FGenericTeamId(0);
    
    EquipmentComponent = CreateDefaultSubobject<UInv_EquipmentComponent>(TEXT("EquipmentComponent"));
}

void AGAS_SlashHeroController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    UE_LOG(LogTemp, Warning, TEXT("OnPossess called"));
    
    if (ACharacter* OwningCharacter = Cast<ACharacter>(InPawn))
    {
        if (EquipmentComponent)
        {
            EquipmentComponent->SetOwningSkeletalMesh(OwningCharacter->GetMesh());
            EquipmentComponent->InitializeOwner(this);
        }

        InventoryComponent = FindComponentByClass<UInv_InventoryComponent>();
        
        if (InventoryComponent)
        {
            UE_LOG(LogTemp, Warning, TEXT("Found Inventory Component, binding delegate"));

            InventoryComponent->OnItemConsumed.AddUniqueDynamic(this, &ThisClass::HandleItemConsumed);

            UE_LOG(LogTemp, Warning, TEXT("Successfully subscribed to the OnItemConsumed"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to find Inventory Component"));
        }
    }
}

void AGAS_SlashHeroController::HandleItemConsumed(FGameplayTag ConsumedItemTag)
{
    UE_LOG(LogTemp, Warning, TEXT("HandleItemConsumed called with tag: %s"), *ConsumedItemTag.ToString());
    
    if(AGAS_SlashHeroCharacter* OwningHeroCharacter = Cast<AGAS_SlashHeroCharacter>(GetCharacter()))
    {
        OwningHeroCharacter->GetSlashAbilitySystemComponent()->TryActivateAbilityByTag(GAS_SlashGameplayTags::Player_Ability_ConsumeItem);
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