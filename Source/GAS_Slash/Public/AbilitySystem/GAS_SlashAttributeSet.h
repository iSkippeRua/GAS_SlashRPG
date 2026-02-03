// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/GAS_SlashAbilitySystemComponent.h"
#include "GAS_SlashAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class IPawnUIInterface;

UCLASS()
class GAS_SLASH_API UGAS_SlashAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UGAS_SlashAttributeSet();

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UGAS_SlashAttributeSet, CurrentHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UGAS_SlashAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Rage")
	FGameplayAttributeData CurrentRage;
	ATTRIBUTE_ACCESSORS(UGAS_SlashAttributeSet, CurrentRage);

	UPROPERTY(BlueprintReadOnly, Category = "Rage")
	FGameplayAttributeData MaxRage;
	ATTRIBUTE_ACCESSORS(UGAS_SlashAttributeSet, MaxRage);

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UGAS_SlashAttributeSet, AttackPower);

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DefencePower;
	ATTRIBUTE_ACCESSORS(UGAS_SlashAttributeSet, DefencePower);

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UGAS_SlashAttributeSet, DamageTaken);

private:
	TWeakInterfacePtr<IPawnUIInterface> CachedPawnUIInterface;
};
