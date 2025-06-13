// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUps/SlashPickUpBase.h"
#include "SlashStoneBase.generated.h"

class UGameplayEffect;
class UGAS_SlashAbilitySystemComponent;

UCLASS()
class GAS_SLASH_API ASlashStoneBase : public ASlashPickUpBase
{
	GENERATED_BODY()

public:
	void Consume(UGAS_SlashAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel);
	
protected:
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Stone Consumed"))
	void BP_OnStoneConsumed();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> StoneGameplayEffectClass;
};
