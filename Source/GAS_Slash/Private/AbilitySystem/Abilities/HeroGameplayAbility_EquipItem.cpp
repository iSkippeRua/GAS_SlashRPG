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

	UE_LOG(LogTemp, Warning, TEXT("HandleEquipItem - ItemTag: %s, SlotTag: %s, IsEquipping: %s"), 
		*EquipData.ItemTag.ToString(), 
		*EquipData.SlotTag.ToString(), 
		EquipData.bIsEquipping ? TEXT("True") : TEXT("False"));

	const TSubclassOf<UGameplayEffect>* FoundEffect = EquipEffectMap.Find(EquipData.ItemTag);
	if (!FoundEffect)
	{
		UE_LOG(LogTemp, Warning, TEXT("No GameplayEffect found for tag: %s"), *EquipData.ItemTag.ToString());
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
			UE_LOG(LogTemp, Warning, TEXT("Successfully applied effect for slot %s"), *EquipData.SlotTag.ToString());
			AbilitySystemComponent->SetActiveEffectForSlot(
				EquipData.SlotTag, 
				NewHandle,
				*FoundEffect,
				EquipData.ItemTag
			);

			if (AbilitySystemComponent->GetActiveGameplayEffect(NewHandle))
			{
				UE_LOG(LogTemp, Warning, TEXT("Effect is active and stored in ASC"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to apply effect for slot %s"), *EquipData.SlotTag.ToString());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unequipping item from slot %s"), *EquipData.SlotTag.ToString());

		const FSlotEffectInfo* SlotInfo = AbilitySystemComponent->GetSlotEffectInfo(EquipData.SlotTag);
		if (SlotInfo && SlotInfo->EffectHandle.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Found existing effect for slot before removal"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Did not found existing effect for slot before removal"));
		}

		if (AbilitySystemComponent->RemoveActiveEffectForSlot(EquipData.SlotTag))
		{
			UE_LOG(LogTemp, Warning, TEXT("Successfully removed effect for slot %s"), *EquipData.SlotTag.ToString());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No effect found to remove for slot %s"), *EquipData.SlotTag.ToString());
		}
	}

	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}
