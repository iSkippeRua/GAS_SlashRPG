// Dmytro Chesniuk All Rights Reserved


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/GAS_SlashAttributeSet.h"
#include "GAS_SlashGameplayTags.h"

#include "SlashDebugHelper.h"

struct FSlashDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefencePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FSlashDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGAS_SlashAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGAS_SlashAttributeSet, DefencePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGAS_SlashAttributeSet, DamageTaken, Target, false)
	}
};

static const FSlashDamageCapture& GetSlashDamageCapture()
{
	static FSlashDamageCapture SlashDamageCapture;
	return SlashDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	RelevantAttributesToCapture.Add(GetSlashDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetSlashDamageCapture().DefencePowerDef);
	RelevantAttributesToCapture.Add(GetSlashDamageCapture().DamageTakenDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetSlashDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);

	float BaseDamage = 0.f;
	int32 UsedLightAttackComboCount = 0.f;
	int32 UsedHeavyAttackComboCount = 0.f;
	
	for(const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if(TagMagnitude.Key.MatchesTagExact(GAS_SlashGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
		}

		if(TagMagnitude.Key.MatchesTagExact(GAS_SlashGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
		}

		if(TagMagnitude.Key.MatchesTagExact(GAS_SlashGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
		}
	}
	
	float TargetDefencePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetSlashDamageCapture().DefencePowerDef, EvaluateParameters, TargetDefencePower);

	if(UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05 + 1.f;

		BaseDamage *= DamageIncreasePercentLight;
	}

	if(UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.15 + 1.f;

		BaseDamage *= DamageIncreasePercentHeavy;
	}

	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefencePower;

	if(FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetSlashDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageDone
			)
		);
	}
}
