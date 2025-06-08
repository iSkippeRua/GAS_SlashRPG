// Dmytro Chesniuk All Rights Reserved


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS_SlashGameplayTags.h"
#include "SlashFunctionLibrary.h"
#include "Characters/GAS_SlashEnemyCharacter.h"
#include "Components/BoxComponent.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if(OverlappedActors.Contains(HitActor)) return;

	OverlappedActors.AddUnique(HitActor);
	
	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = USlashFunctionLibrary::NativeDoesActorHaveTag(HitActor, GAS_SlashGameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable = USlashFunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), GAS_SlashGameplayTags::Enemy_Status_Unblockable);

	if(bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		bIsValidBlock = USlashFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if(bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			GAS_SlashGameplayTags::Player_Event_SuccessfulBlock,
			EventData
		);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			GAS_SlashGameplayTags::Shared_Event_MeleeHit,
			EventData
		);
	}
}

void UEnemyCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	AGAS_SlashEnemyCharacter* OwningEnemyCharacter = GetOwningPawn<AGAS_SlashEnemyCharacter>();

	check(OwningEnemyCharacter);

	UBoxComponent* LeftHandCollisionBox = OwningEnemyCharacter->GetLeftHandCollisionBox();
	UBoxComponent* RightHandCollisionBox = OwningEnemyCharacter->GetRightHandCollisionBox();

	check(LeftHandCollisionBox && RightHandCollisionBox);

	switch(ToggleDamageType)
	{
	case EToggleDamageType::LeftHand:
		LeftHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
		
	case EToggleDamageType::RightHand:
		RightHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
		
	default:
		break;
	}

	if(!bShouldEnable)
	{
		OverlappedActors.Empty();
	}
}
