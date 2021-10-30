// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
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

void UItemWidget::NativeOnDragDetected(const FGeometry& MovieSceneBlends, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(MovieSceneBlends, InMouseEvent, OutOperation);

	if(DragDropOperationClass == nullptr) return;
	DragDropOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(DragDropOperationClass);
	
	if(ItemData == nullptr || DragDropOperation == nullptr) return;

	DragDropOperation->Payload = ItemData;
	DragDropOperation->DefaultDragVisual = this;
	DragDropOperation->Pivot = EDragPivot::CenterCenter;

	OutOperation = DragDropOperation;

	RemoveEvent.Broadcast(ItemData);
	RemoveFromParent();
}

FReply UItemWidget::NativeOnMouseButtonDown(const FGeometry& MovieSceneBlends, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(MovieSceneBlends, InMouseEvent);
	
	FEventReply Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	return Reply.NativeReply;
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
