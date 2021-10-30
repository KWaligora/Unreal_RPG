// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"

#include "Components/Border.h"
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

void UItemWidget::NativeOnMouseEnter(const FGeometry& MovieSceneBlends, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(MovieSceneBlends, InMouseEvent);
	if(BackgroundBorder == nullptr) return;
	BackgroundBorder->SetBrushColor(FLinearColor(0.5, 0.5, 0.5, 0.2));	
}

void UItemWidget::NativeOnMouseLeave(const FPointerEvent& MovieSceneBlends)
{
	Super::NativeOnMouseLeave(MovieSceneBlends);
	if(BackgroundBorder == nullptr) return;

	BackgroundBorder->SetBrushColor(FLinearColor(0, 0, 0, 0.5));
}

// Refresh item visual representation in inventory
void UItemWidget::Refresh()
{	
	if(BackgroundSizeBox == nullptr || ItemImage == nullptr || ItemData == nullptr) return;
	
	FVector2D ItemDimensions = ItemData->GetDimensions();
	Size = ItemDimensions * TileSize;
	
	BackgroundSizeBox->HeightOverride = Size.Y;
	BackgroundSizeBox->WidthOverride = Size.X;

	if(UCanvasPanelSlot* ItemImageBoxSlot = Cast<UCanvasPanelSlot>(ItemImage->Slot))
	{
		ItemImageBoxSlot->SetSize(Size);
	}
	
	ItemImage->SetBrushFromMaterial(ItemData->GetIcon());
}
