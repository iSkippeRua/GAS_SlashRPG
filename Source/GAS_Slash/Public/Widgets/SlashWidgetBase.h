// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlashWidgetBase.generated.h"

class UEnemyUIComponent;
class UHeroUIComponent;

UCLASS()
class GAS_SLASH_API USlashWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Hero UI Component Initialized"))
	void BP_OnOwningHeroUIComponentInitialized(UHeroUIComponent* OwningHeroUIComponent);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Enemy UI Component Initialized"))
	void BP_OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* OwningEnemyUIComponent);

public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreatedWidget(AActor* OwningEnemyActor);
	
};
