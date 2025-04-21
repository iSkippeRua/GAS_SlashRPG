// Dmytro Chesniuk All Rights Reserved


#include "Characters/GAS_SlashHeroCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/GAS_SlashInputComponent.h"
#include "GAS_SlashGameplayTags.h"
#include "AbilitySystem/GAS_SlashAbilitySystemComponent.h"

AGAS_SlashHeroCharacter::AGAS_SlashHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void AGAS_SlashHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(SlashAbilitySystemComponent && SlashAttributeSet)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owner Actor: %s, Avatar Actor: %s"), *SlashAbilitySystemComponent->GetOwnerActor()->GetActorLabel(), *SlashAbilitySystemComponent->GetAvatarActor()->GetActorLabel());
	}
}

void AGAS_SlashHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"))
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UGAS_SlashInputComponent* GAS_SlashInputComponent = CastChecked<UGAS_SlashInputComponent>(PlayerInputComponent);
	GAS_SlashInputComponent->BindNativeInputAction(InputConfigDataAsset, GAS_SlashGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	GAS_SlashInputComponent->BindNativeInputAction(InputConfigDataAsset, GAS_SlashGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
}

void AGAS_SlashHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if(MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
	
	if(MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AGAS_SlashHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	
	if(LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if(LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
