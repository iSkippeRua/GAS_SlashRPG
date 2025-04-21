// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/GAS_SlashBaseCharacter.h"
#include "GAS_SlashHeroCharacter.generated.h"

class UDataAsset_InputConfig;
class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class GAS_SLASH_API AGAS_SlashHeroCharacter : public AGAS_SlashBaseCharacter
{
	GENERATED_BODY()
	
public:
	AGAS_SlashHeroCharacter();
	
protected:
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
private:
	
#pragma region Components
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
#pragma endregion

#pragma region Inputs
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Data", meta=(AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	
#pragma endregion 
};
