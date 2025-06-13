// Dmytro Chesniuk All Rights Reserved


#include "Items/PickUps/SlashStoneBase.h"
#include "Characters/GAS_SlashHeroCharacter.h"
#include "AbilitySystem/GAS_SlashAbilitySystemComponent.h"
#include "GAS_SlashGameplayTags.h"

void ASlashStoneBase::Consume(UGAS_SlashAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel)
{
	check(StoneGameplayEffectClass);

	UGameplayEffect* EffectCDO = StoneGameplayEffectClass->GetDefaultObject<UGameplayEffect>();
	
	AbilitySystemComponent->ApplyGameplayEffectToSelf(
		EffectCDO,
		ApplyLevel,
		AbilitySystemComponent->MakeEffectContext()
	);

	BP_OnStoneConsumed();
}

void ASlashStoneBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AGAS_SlashHeroCharacter* OverlappedHeroCharacter = Cast<AGAS_SlashHeroCharacter>(OtherActor))
	{
		OverlappedHeroCharacter->GetSlashAbilitySystemComponent()->TryActivateAbilityByTag(GAS_SlashGameplayTags::Player_Ability_PickUp_Stones);
	}
}
