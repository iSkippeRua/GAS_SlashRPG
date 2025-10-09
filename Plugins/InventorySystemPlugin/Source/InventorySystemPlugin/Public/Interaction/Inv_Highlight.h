// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Inv_Highlight.generated.h"

UINTERFACE()
class UInv_Highlight : public UInterface
{
	GENERATED_BODY()
};

class INVENTORYSYSTEMPLUGIN_API IInv_Highlight
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Inventory")
	void Highlight();

	UFUNCTION(BlueprintNativeEvent, Category = "Inventory")
	void UnHighlight();
};
