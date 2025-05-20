// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Interfaces/PawnUIInterface.h"
#include "GAS_SlashBaseCharacter.generated.h"

class UDataAsset_StartUpDataBase;
class UGAS_SlashAttributeSet;
class UGAS_SlashAbilitySystemComponent;

UCLASS()
class GAS_SLASH_API AGAS_SlashBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()

public:
	AGAS_SlashBaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	
protected:
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UGAS_SlashAbilitySystemComponent* SlashAbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UGAS_SlashAttributeSet* SlashAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;

public:
	FORCEINLINE UGAS_SlashAbilitySystemComponent* GetSlashAbilitySystemComponent() const { return SlashAbilitySystemComponent; }
	FORCEINLINE UGAS_SlashAttributeSet* GetSlashAttributeSet() const { return SlashAttributeSet; }
	
};
