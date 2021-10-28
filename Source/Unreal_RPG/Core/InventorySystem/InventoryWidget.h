// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

UCLASS()
class UNREAL_RPG_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
		
public:	
	FVector2D GetGridSize() {return GridSize;}
	
private:
	UPROPERTY(meta = (BindWidget))
	class UInventoryGrid* WPB_InventoryGrid;

	// Columns/Rows
	FVector2D GridSize = FVector2D(15, 5);

protected:
	virtual void NativeOnInitialized() override;
};
