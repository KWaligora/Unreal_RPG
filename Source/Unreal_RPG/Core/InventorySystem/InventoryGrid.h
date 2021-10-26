// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGrid.generated.h"

class UInventoryComponent;

UCLASS()
class UNREAL_RPG_API UInventoryGrid : public UUserWidget
{
	GENERATED_BODY()

public:
	void CreateGrid(FVector2D GridSize);
	UFUNCTION(BlueprintCallable)
	void Paint(FPaintContext Context) const;
	
private:

	UPROPERTY(meta = (BindWidget))
	class UBorder* GridBorder;
	
	float TileSize = 50.0;

	TArray<FVector4> Lines;
};
