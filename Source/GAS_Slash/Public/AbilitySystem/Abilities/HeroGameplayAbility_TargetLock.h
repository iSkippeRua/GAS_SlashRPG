// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GAS_SlashHeroGameplayAbility.h"
#include "HeroGameplayAbility_TargetLock.generated.h"

class UInputMappingContext;
class USlashWidgetBase;

UCLASS()
class GAS_SLASH_API UHeroGameplayAbility_TargetLock : public UGAS_SlashHeroGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintCallable)
	void OnTargetLockTick(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void SwitchTarget(const FGameplayTag& InSwitchDirectionTag);
	
private:
	void TryLockOnTarget();
	void GetAvailableActorsToLock();
	AActor* GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors);
	void GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight);
	void DrawTargetLockWidget();
	void SetTargetLockWidgetPosition();
	void InitTargetLockMovement();
	void InitTargetLockMappingContext();

	void CancelTargetLockAbility();
	void CleanUp();
	void ResetTargetLockMovement();
	void ResetTargetLockMappingContext();

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float BoxTraceDistance = 5000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	FVector TraceBoxSize = FVector(500.f, 500.f, 300.f);

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	TArray<TEnumAsByte<EObjectTypeQuery>> BoxTraceChannel;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	bool bShowPersistentDebugShape = false;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	TSubclassOf<USlashWidgetBase> TargetLockWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float TargetLockRotationInterpSpeed = 5.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float TargetLockMaxWalkSpeed = 150.f;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	UInputMappingContext* TargetLockMappingContext;

	UPROPERTY()
	TArray<AActor*> AvailableActorsToLock;

	UPROPERTY()
	AActor* CurrentLockedActor;

	UPROPERTY()
	USlashWidgetBase* DrawnTargetLockWidget;

	UPROPERTY()
	FVector2D TargetLockWidgetSize = FVector2D::ZeroVector;

	UPROPERTY()
	float CachedDefaultMaxWalkSpeed = 0.f;
};
