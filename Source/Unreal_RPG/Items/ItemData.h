// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemData.generated.h"

class AItemBase;

UCLASS(Blueprintable, BlueprintType)
class UNREAL_RPG_API UItemData : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay="Parameter1, Parameter2, Parameter3"))
	void Initialise(FVector2D NewDimensions, UMaterialInterface* NewIcon, TSubclassOf<AItemBase> NewItem);
	
	FVector2D GetDimensions() const {return Dimensions;}	
	UMaterialInterface* GetIcon() const {return Icon; }
	
private:	
	FVector2D Dimensions;
	UPROPERTY()
	UMaterialInterface* Icon;	
	TSubclassOf<AItemBase> Item;
};
