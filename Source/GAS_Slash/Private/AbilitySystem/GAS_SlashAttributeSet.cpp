// Dmytro Chesniuk All Rights Reserved


#include "AbilitySystem/GAS_SlashAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "SlashFunctionLibrary.h"
#include "GAS_SlashGameplayTags.h"
#include "Interfaces/PawnUIInterface.h"
#include "Components/UI/PawnUIComponent.h"
#include "Components/UI/HeroUIComponent.h"

#include "SlashDebugHelper.h"

UGAS_SlashAttributeSet::UGAS_SlashAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefencePower(1.f);
}

void UGAS_SlashAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if(!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}

	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();

	checkf(PawnUIComponent, TEXT("Couldn't extract a PawnUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());
	
	if(Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}

	if(Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());

		SetCurrentRage(NewCurrentRage);

		if(UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
		{
			HeroUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
		}
	}

	if(Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();

		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		const FString DebugString = FString::Printf(
			TEXT("Old health: %f, Damage Done: %f, NewCurrentHealth: %f"), OldHealth, DamageDone, NewCurrentHealth
		);

		Debug::Print(DebugString, FColor::Emerald);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());

		if(GetCurrentHealth() == 0.f)
		{
			USlashFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), GAS_SlashGameplayTags::Shared_Status_Dead);
		}
	}
}
