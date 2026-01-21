// Dmytro Chesniuk All Rights Reserved

#include "Shop/Shop_AreaVolume.h"
#include "Characters/GAS_SlashHeroCharacter.h"
#include "Shop/Shop_InteractionComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Controllers/GAS_SlashHeroController.h"

AShop_AreaVolume::AShop_AreaVolume()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = false;
	
	ShopMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShopMesh"));
	ShopMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ShopMesh->SetCollisionObjectType(ECC_WorldStatic);
	ShopMesh->SetCollisionResponseToAllChannels(ECR_Block);
	RootComponent = ShopMesh;
	
	ShopAreaBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ShopAreaBox"));
	ShopAreaBox->SetupAttachment(ShopMesh);
	ShopAreaBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ShopAreaBox->SetCollisionObjectType(ECC_WorldStatic);
	ShopAreaBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	ShopAreaBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ShopAreaBox->SetBoxExtent(ShopAreaBoxExtent);
	
	ShopInteractionComponent = CreateDefaultSubobject<UShop_InteractionComponent>(TEXT("ShopInteractionComponent"));
}

void AShop_AreaVolume::BeginPlay()
{
	Super::BeginPlay();
	
	if (ShopAreaBox)
	{
		ShopAreaBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnShopAreaBeginOverlap);
		ShopAreaBox->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnShopAreaEndOverlap);
	}
}

void AShop_AreaVolume::OnShopAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor))
		return;
	
	AGAS_SlashHeroCharacter* HeroCharacter = Cast<AGAS_SlashHeroCharacter>(OtherActor);
	if (!HeroCharacter)
		return;
	
	AGAS_SlashHeroController* HeroController = Cast<AGAS_SlashHeroController>(HeroCharacter->GetController());
	if (HeroController && ShopInteractionComponent)
	{
		HeroController->SetCurrentShop(ShopInteractionComponent);
		ShopInteractionComponent->OnPlayerEnterShopArea(HeroController);
	}
}

void AShop_AreaVolume::OnShopAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsValid(OtherActor))
		return;
	
	AGAS_SlashHeroCharacter* HeroCharacter = Cast<AGAS_SlashHeroCharacter>(OtherActor);
	if (!HeroCharacter)
		return;
	
	AGAS_SlashHeroController* HeroController = Cast<AGAS_SlashHeroController>(HeroCharacter->GetController());
	if (HeroController && ShopInteractionComponent)
	{
		ShopInteractionComponent->OnPlayerLeaveShopArea(HeroController);
		HeroController->SetCurrentShop(nullptr);
	}
}
