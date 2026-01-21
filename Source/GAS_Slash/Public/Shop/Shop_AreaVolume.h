// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shop_AreaVolume.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UShop_InteractionComponent;
class AGAS_SlashHeroCharacter;
class AGAS_SlashHeroController;

UCLASS()
class GAS_SLASH_API AShop_AreaVolume : public AActor
{
	GENERATED_BODY()
	
public:
	AShop_AreaVolume();
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	UShop_InteractionComponent* GetShopComponent() const { return ShopInteractionComponent; }
	
	UFUNCTION(BlueprintCallable, Category = "Shop")
	UStaticMeshComponent* GetShopMesh() const { return ShopMesh; }
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop")
	TObjectPtr<UStaticMeshComponent> ShopMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop")
	TObjectPtr<UBoxComponent> ShopAreaBox;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop")
	TObjectPtr<UShop_InteractionComponent> ShopInteractionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	FVector ShopAreaBoxExtent = FVector(500.f, 500.f, 300.f);
	
private:
	UFUNCTION()
	void OnShopAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnShopAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};