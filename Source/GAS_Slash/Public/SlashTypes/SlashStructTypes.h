// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "GameplayEffectTypes.h"
#include "SlashStructTypes.generated.h"

class UInputMappingContext;
class UGAS_SlashHeroLinkedAnimLayer;
class UGAS_SlashHeroGameplayAbility;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FSlashHeroAbilitySet
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGAS_SlashHeroGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};

USTRUCT(BlueprintType)
struct FSlashHeroSpecialAbilitySet : public FSlashHeroAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UMaterialInterface> SoftAbilityIconMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Player.Cooldown"))
	FGameplayTag AbilityCooldownTag;
};

USTRUCT(BlueprintType)
struct FGAS_SlashHeroWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGAS_SlashHeroLinkedAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FSlashHeroAbilitySet> DefaultWeaponAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FSlashHeroSpecialAbilitySet> SpecialWeaponAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> SoftWeaponIconTexture;
};

USTRUCT(BlueprintType)
struct FEquipItemData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag ItemTag;

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag SlotTag;

	UPROPERTY(BlueprintReadWrite)
	bool bIsEquipping;

	FEquipItemData()
		: ItemTag(FGameplayTag::EmptyTag)
		, SlotTag(FGameplayTag::EmptyTag)
		, bIsEquipping(false)
	{}
	
	FEquipItemData(const FGameplayTag& InItemTag, const FGameplayTag& InSlotTag, bool bInIsEquipping)
		: ItemTag(InItemTag)
		, SlotTag(InSlotTag)
		, bIsEquipping(bInIsEquipping)
	{}
};

USTRUCT(BlueprintType)
struct FSlotEffectInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FActiveGameplayEffectHandle EffectHandle;
	
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> EffectClass;

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag ItemTag;

	FSlotEffectInfo()
		: EffectHandle(FActiveGameplayEffectHandle())
		, EffectClass(nullptr)
		, ItemTag(FGameplayTag::EmptyTag)
	{}

	FSlotEffectInfo(const FActiveGameplayEffectHandle& InHandle, TSubclassOf<UGameplayEffect> InEffectClass, const FGameplayTag& InItemTag)
		: EffectHandle(InHandle)
		, EffectClass(InEffectClass)
		, ItemTag(InItemTag)
	{}
};