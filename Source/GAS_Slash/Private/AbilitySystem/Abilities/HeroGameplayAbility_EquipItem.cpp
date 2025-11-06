// Dmytro Chesniuk All Rights Reserved


#include "AbilitySystem/Abilities/HeroGameplayAbility_EquipItem.h"
#include "AbilitySystem/GAS_SlashAbilitySystemComponent.h"
#include "SlashTypes/SlashStructTypes.h"

void UHeroGameplayAbility_EquipItem::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                     const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                     const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UHeroGameplayAbility_EquipItem::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UHeroGameplayAbility_EquipItem::HandleEquipItem()
{
	UGAS_SlashAbilitySystemComponent* AbilitySystemComponent = GetSlashAbilitySystemComponentFromActorInfo();
	if (!AbilitySystemComponent)
	{
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
		return;
	}

	FEquipItemData EquipData = AbilitySystemComponent->GetEquipItemData();

	const TSubclassOf<UGameplayEffect>* FoundEffect = EquipEffectMap.Find(EquipData.ItemTag);
	if (!FoundEffect)
	{
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
		return;
	}

	if (EquipData.bIsEquipping)
	{
		AbilitySystemComponent->RemoveActiveEffectForSlot(EquipData.SlotTag);

		FActiveGameplayEffectHandle NewHandle = AbilitySystemComponent->ApplyGameplayEffectToSelf(
			(*FoundEffect)->GetDefaultObject<UGameplayEffect>(),
			GetAbilityLevel(),
			AbilitySystemComponent->MakeEffectContext()
		);

		if (NewHandle.IsValid())
		{
			AbilitySystemComponent->SetActiveEffectForSlot(
				EquipData.SlotTag, 
				NewHandle,
				*FoundEffect,
				EquipData.ItemTag
			);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to apply effect for slot %s"), *EquipData.SlotTag.ToString());
		}
	}
	else
	{
		AbilitySystemComponent->RemoveActiveEffectForSlot(EquipData.SlotTag);
	}

	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}
