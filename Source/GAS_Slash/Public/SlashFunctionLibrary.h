// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SlashTypes/SlashEnumTypes.h"
#include "SlashFunctionLibrary.generated.h"

struct FGameplayEffectSpecHandle;
class UPawnCombatComponent;
struct FGameplayTag;
class UGAS_SlashAbilitySystemComponent;
struct FScalableFloat;

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

	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);
	
	UFUNCTION(BlueprintCallable, Category = "GAS_Slash|FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, ESlashValidType& OutValidType);

	UFUNCTION(BlueprintPure, Category = "GAS_Slash|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category = "GAS_Slash|FunctionLibrary", meta = (CompactNodeTitle = "Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel = 1.f);

	UFUNCTION(BlueprintPure, Category = "GAS_Slash|FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

	UFUNCTION(BlueprintPure, Category = "GAS_Slash|FunctionLibrary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);

	UFUNCTION(BlueprintCallable, Category = "GAS_Slash|FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "GAS_Slash|FunctionLibrary", meta = (Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo", ExpandEnumAsExecs = "CountDownInput|CountDownOutput", TotalTime = "1.0", UpdateInterval = "0.1"))
	static void CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainingTime, ESlashCountDownActionInput CountDownInput, ESlashCountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo);
};
