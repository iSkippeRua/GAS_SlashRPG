// Dmytro Chesniuk All Rights Reserved


#include "SlashFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/GAS_SlashAbilitySystemComponent.h"

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

