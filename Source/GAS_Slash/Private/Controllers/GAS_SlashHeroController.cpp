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
    
    if (ACharacter* OwningCharacter = Cast<ACharacter>(InPawn))
    {
        if (EquipmentComponent)
        {
            EquipmentComponent->SetOwningSkeletalMesh(OwningCharacter->GetMesh());
            EquipmentComponent->InitializeOwner(this);

            EquipmentComponent->OnItemEquippedSignal.AddUniqueDynamic(this, &ThisClass::HandleItemEquipped);
            EquipmentComponent->OnItemUnequippedSignal.AddUniqueDynamic(this, &ThisClass::HandleItemUnequipped);
        }

        InventoryComponent = FindComponentByClass<UInv_InventoryComponent>();
        
        if (InventoryComponent)
        {
            InventoryComponent->OnItemConsumed.AddUniqueDynamic(this, &ThisClass::HandleItemConsumed);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to find Inventory Component"));
        }
    }
}

void AGAS_SlashHeroController::HandleItemConsumed(FGameplayTag ConsumedItemTag)
{
    if(AGAS_SlashHeroCharacter* OwningHeroCharacter = Cast<AGAS_SlashHeroCharacter>(GetCharacter()))
    {
        OwningHeroCharacter->GetSlashAbilitySystemComponent()->SetLastConsumedItemTag(ConsumedItemTag);
        OwningHeroCharacter->GetSlashAbilitySystemComponent()->TryActivateAbilityByTag(GAS_SlashGameplayTags::Player_Ability_ConsumeItem);
    }
}

void AGAS_SlashHeroController::HandleItemEquipped(FGameplayTag EquippedItemType, FGameplayTag EquippedItemSlot)
{
    if(AGAS_SlashHeroCharacter* OwningHeroCharacter = Cast<AGAS_SlashHeroCharacter>(GetCharacter()))
    {
        OwningHeroCharacter->GetSlashAbilitySystemComponent()->SetEquipItemData(
            EquippedItemType,
            EquippedItemSlot,
            true
        );
        OwningHeroCharacter->GetSlashAbilitySystemComponent()->TryActivateAbilityByTag(GAS_SlashGameplayTags::Player_Ability_EquipItem);
    }
}

void AGAS_SlashHeroController::HandleItemUnequipped(FGameplayTag UnequippedItemType, FGameplayTag UnequippedItemSlot)
{
    if(AGAS_SlashHeroCharacter* OwningHeroCharacter = Cast<AGAS_SlashHeroCharacter>(GetCharacter()))
    {
        OwningHeroCharacter->GetSlashAbilitySystemComponent()->SetEquipItemData(
            UnequippedItemType,
            UnequippedItemSlot,
            false
        );
        OwningHeroCharacter->GetSlashAbilitySystemComponent()->TryActivateAbilityByTag(GAS_SlashGameplayTags::Player_Ability_EquipItem);
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