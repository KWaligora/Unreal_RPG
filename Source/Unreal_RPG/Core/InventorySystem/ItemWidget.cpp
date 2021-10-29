// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Unreal_RPG/Items/ItemData.h"

void UItemWidget::Initialise(int NewTileSize, UItemData* NewItemData)
{
	TileSize = NewTileSize;
	ItemData = NewItemData;

	Refresh();
}

// Refresh item visual representation in inventory
void UItemWidget::Refresh()
{	
	if(BackgroundSizeBox == nullptr || ItemImage == nullptr || ItemData == nullptr) return;
	
	FVector2D ItemDimensions = ItemData->GetDimensions();
	Size = ItemDimensions * TileSize;

	if(UCanvasPanelSlot* SizeBoxSlot = Cast<UCanvasPanelSlot>(BackgroundSizeBox->Slot))
	{
		SizeBoxSlot->SetSize(Size);
	}

	if(UCanvasPanelSlot* ItemImageBoxSlot = Cast<UCanvasPanelSlot>(ItemImage->Slot))
	{
		ItemImageBoxSlot->SetSize(Size);
	}
	
	ItemImage->SetBrushFromMaterial(ItemData->GetIcon());
}
