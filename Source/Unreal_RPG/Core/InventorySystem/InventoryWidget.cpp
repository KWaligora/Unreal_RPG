// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

#include "InventoryGrid.h"

void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(InventoryGrid == nullptr) return;

	InventoryGrid->CreateGrid(FVector2D(5,15));
}
