// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemData.h"


void UItemData::Initialise(FVector2D NewDimensions, UMaterialInterface* NewIcon, TSubclassOf<AItemBase> NewItem)
{
	Dimensions = NewDimensions;
	Icon = NewIcon;
	ItemClass = NewItem;
}
