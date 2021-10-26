// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

#include "InventoryGrid.h"

void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(WPB_InventoryGrid == nullptr) return;

	WPB_InventoryGrid->CreateGrid(FVector2D(5,15));
}
