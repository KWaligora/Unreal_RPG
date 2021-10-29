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
	
private:
	// Event Handle
	FRemoveEvent RemoveEvent;
	
	// Refresh item visual representation in inventory
	void Refresh();

	UPROPERTY(meta = (BindWidget))
	class USizeBox* BackgroundSizeBox;
	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;
	
	UPROPERTY()
	UItemData* ItemData = nullptr;
	int TileSize = 50;
	FVector2D Size;
};
