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
	FVector2D GridSize = FVector2D(5, 15);
	
private:
	UPROPERTY(meta = (BindWidget))
	class UInventoryGrid* WPB_InventoryGrid;	

protected:
	virtual void NativeOnInitialized() override;
};
