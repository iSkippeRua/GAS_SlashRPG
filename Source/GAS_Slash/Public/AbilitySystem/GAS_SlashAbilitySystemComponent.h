// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SlashTypes/SlashStructTypes.h"
#include "GAS_SlashAbilitySystemComponent.generated.h"

UCLASS()
class GAS_SLASH_API UGAS_SlashAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	UFUNCTION(BlueprintCallable, Category = "GAS_Slash|Ability", meta = (ApplyLevel = "1"))
	void GrantHeroWeaponAbilities(const TArray<FSlashHeroAbilitySet>& InDefaultWeaponAbilities, const TArray<FSlashHeroSpecialAbilitySet>& InSpecialWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);

	UFUNCTION(BlueprintCallable, Category = "GAS_Slash|Ability")
	void RemoveGrantedHeroWeaponAbilities(UPARAM(ref)TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);

	UFUNCTION(BlueprintCallable, Category = "GAS_Slash|Ability")
	bool TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate);

	void SetLastConsumedItemTag(const FGameplayTag& Tag) { LastConsumedItemTag = Tag; }
	FGameplayTag GetLastConsumedItemTag() const { return LastConsumedItemTag; }

	void SetEquipItemData(const FGameplayTag& ItemTag, const FGameplayTag& SlotTag, bool bIsEquipping)
	{
		CurrentEquipData.ItemTag = ItemTag;
		CurrentEquipData.SlotTag = SlotTag;
		CurrentEquipData.bIsEquipping = bIsEquipping;
	}
	FEquipItemData GetEquipItemData() const { return CurrentEquipData; }
	void SetActiveEffectForSlot(const FGameplayTag& SlotTag, const FActiveGameplayEffectHandle& Handle, TSubclassOf<UGameplayEffect> EffectClass, const FGameplayTag& ItemTag);
	bool RemoveActiveEffectForSlot(const FGameplayTag& SlotTag);
	const FSlotEffectInfo* GetSlotEffectInfo(const FGameplayTag& SlotTag) const;

private:
	FGameplayTag LastConsumedItemTag;
	
	FEquipItemData CurrentEquipData;
	TMap<FGameplayTag, FSlotEffectInfo> SlotToEffectMap;
};
