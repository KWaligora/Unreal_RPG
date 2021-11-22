// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ItemWidget.generated.h"

class UItemData;

UCLASS()
class UNREAL_RPG_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_EVENT_OneParam(UItemWidget, FRemoveEvent, UItemData*)
	FRemoveEvent& OnRemove() {return RemoveEvent;}
	
	void Initialise(int NewTileSize, UItemData* NewItemData);

	// Events override
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;	
	
private:
	// Event Handle
	FRemoveEvent RemoveEvent;
	
	// Refresh item visual representation in inventory
	void Refresh();

	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UDragDropOperation> DragDropOperationClass;

	UPROPERTY()
	UDragDropOperation* DragDropOperation;
	
	UPROPERTY(meta = (BindWidget))
	class USizeBox* BackgroundSizeBox;
	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;
	UPROPERTY(meta = (BindWidget))
	class UBorder* BackgroundBorder;
	
	UPROPERTY()
	UItemData* ItemData = nullptr;
	int TileSize = 50;
	FVector2D Size;
};
