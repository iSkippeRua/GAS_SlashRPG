// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SlashFunctionLibrary.generated.h"

struct FGameplayTag;
class UGAS_SlashAbilitySystemComponent;

UENUM()
enum class ESlashConfirmType : uint8
{
	Yes,
	No
};

UCLASS()
class GAS_SLASH_API USlashFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UGAS_SlashAbilitySystemComponent* NativeGetSlashASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "GAS_Slash|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);
	
	UFUNCTION(BlueprintCallable, Category = "GAS_Slash|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "GAS_Slash|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, ESlashConfirmType& OutConfirmType);
};
