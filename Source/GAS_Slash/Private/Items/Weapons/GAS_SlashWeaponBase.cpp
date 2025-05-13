// Dmytro Chesniuk All Rights Reserved


#include "Items/Weapons/GAS_SlashWeaponBase.h"
#include "Components/BoxComponent.h"

AGAS_SlashWeaponBase::AGAS_SlashWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);
}

void AGAS_SlashWeaponBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forgot to assign an instigator as the owning pawn for the weapon: %s"), *GetName());

	if(APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if(WeaponOwningPawn != HitPawn)
		{
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
		}
	}
}

void AGAS_SlashWeaponBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forgot to assign an instigator as the owning pawn for the weapon: %s"), *GetName());

	if(APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if(WeaponOwningPawn != HitPawn)
		{
			OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
		}
	}
}