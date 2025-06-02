// Dmytro Chesniuk All Rights Reserved


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS_SlashGameplayTags.h"
#include "SlashFunctionLibrary.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if(OverlappedActors.Contains(HitActor)) return;

	OverlappedActors.AddUnique(HitActor);
	
	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = USlashFunctionLibrary::NativeDoesActorHaveTag(HitActor, GAS_SlashGameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable = false;

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
