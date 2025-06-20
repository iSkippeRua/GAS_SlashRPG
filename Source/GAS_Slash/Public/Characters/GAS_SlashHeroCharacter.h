// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/GAS_SlashBaseCharacter.h"
#include "GameplayTagContainer.h"
#include "GAS_SlashHeroCharacter.generated.h"

class UDataAsset_InputConfig;
class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;
class UHeroCombatComponent;
class UHeroUIComponent;

UCLASS()
class GAS_SLASH_API AGAS_SlashHeroCharacter : public AGAS_SlashBaseCharacter
{
	GENERATED_BODY()
	
public:
	AGAS_SlashHeroCharacter();

	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

	virtual UPawnUIComponent* GetPawnUIComponent() const override;

	virtual UHeroUIComponent* GetHeroUIComponent() const override;

protected:
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
private:
	
#pragma region Components
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess = "true"))
	UHeroCombatComponent* HeroCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess = "true"))
	UHeroUIComponent* HeroUIComponent;
	
#pragma endregion

#pragma region Inputs
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Data", meta=(AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	UPROPERTY()
	FVector2D SwitchDirection = FVector2D::ZeroVector;
	
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	
	void Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue);
	void Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue);

	void Input_PickUpStonesStarted(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);
	
#pragma endregion

public:
	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent() const { return HeroCombatComponent; }
};
