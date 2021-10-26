// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

UCLASS()
class UNREAL_RPG_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UInventoryGrid* InventoryGrid;	
};
