// Dmytro Chesniuk All Rights Reserved


#include "SlashFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/GAS_SlashAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "GAS_SlashGameplayTags.h"

UGAS_SlashAbilitySystemComponent* USlashFunctionLibrary::NativeGetSlashASCFromActor(AActor* InActor)
{
	check(InActor);

	return CastChecked<UGAS_SlashAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void USlashFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UGAS_SlashAbilitySystemComponent* ASC = NativeGetSlashASCFromActor(InActor);

	if(!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void USlashFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UGAS_SlashAbilitySystemComponent* ASC = NativeGetSlashASCFromActor(InActor);

	if(ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool USlashFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UGAS_SlashAbilitySystemComponent* ASC = NativeGetSlashASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void USlashFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck,
	ESlashConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? ESlashConfirmType::Yes : ESlashConfirmType::No;
}

UPawnCombatComponent* USlashFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if(IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UPawnCombatComponent* USlashFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor,
	ESlashValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);
	
	OutValidType = CombatComponent ? ESlashValidType::Valid : ESlashValidType::Invalid;

	return CombatComponent;
}

bool USlashFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);
	
	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if(QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}

	return false;
}

float USlashFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag USlashFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim,
	float& OutAngleDifference)
{
	check(InAttacker && InVictim);

	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalized);
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormalized);

	if(CrossResult.Z < 0.f)
	{
		OutAngleDifference *= -1.f;
	}

	if(OutAngleDifference >= -45.f && OutAngleDifference <= 45.f)
	{
		return GAS_SlashGameplayTags::Shared_Status_HitReact_Front;
	} else if(OutAngleDifference < -45.f && OutAngleDifference >= -135.f)
	{
		return GAS_SlashGameplayTags::Shared_Status_HitReact_Left;
	} else if(OutAngleDifference < -135.f || OutAngleDifference > 135.f)
	{
		return GAS_SlashGameplayTags::Shared_Status_HitReact_Back;	
	} else if(OutAngleDifference > 45.f && OutAngleDifference <= 135.f)
	{
		return GAS_SlashGameplayTags::Shared_Status_HitReact_Right;	
	}

	return GAS_SlashGameplayTags::Shared_Status_HitReact_Front;
}

bool USlashFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	check(InAttacker && InDefender);

	const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());

	return DotResult < -0.1f;
}

bool USlashFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle)
{
	UGAS_SlashAbilitySystemComponent* SourceASC = NativeGetSlashASCFromActor(InInstigator);
	UGAS_SlashAbilitySystemComponent* TargetASC = NativeGetSlashASCFromActor(InTargetActor);

	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);

	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}
