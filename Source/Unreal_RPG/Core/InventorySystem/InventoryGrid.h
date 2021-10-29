// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGrid.generated.h"

class UItemWidget;
class UItemData;

UCLASS()
class UNREAL_RPG_API UInventoryGrid : public UUserWidget
{
	GENERATED_BODY()

public:
	UInventoryGrid(const FObjectInitializer & ObjectInitializer);
	
	void CreateGrid(FVector2D GridSize);
	
	// Called by blueprint OnPaint event
	UFUNCTION(BlueprintCallable)
	void Paint(FPaintContext Context) const;
	
private:
// Functions
	// Getting inventory component
	virtual void NativeOnInitialized() override;
	void Refresh();
	void OnItemRemoved(UItemData* ItemData);

// Variables
	UPROPERTY(meta = (BindWidget))
	class UBorder* GridBorder;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* GridCanvasPanel;

	TSubclassOf<UUserWidget> ItemWidgetClass;

	UPROPERTY()
	class UInventoryComponent* InventoryComponent = nullptr;

	TArray<UItemWidget*> ItemsWidget;
	
	float TileSize = 50.0;
	
	// Grid Lines
	TArray<FVector4> Lines;
};
