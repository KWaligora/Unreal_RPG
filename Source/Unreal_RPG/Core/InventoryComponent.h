// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_RPG_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	DECLARE_EVENT(UInventoryComponent, FInventoryChangedEvent)
	FInventoryChangedEvent& OnInventoryChanged() {return InventoryChangedEvent; }
	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

// Variables
	bool bIsOpened = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Show/Hide inventory
	void ToggleInventoryWidget();
	bool AddItem(UItemData* ItemData);
	TMap<UItemData*, FVector2D> GetAllItems();
	void RemoveItem(UItemData* ItemData);
	
private:
// Variables
	// Invent handle
	FInventoryChangedEvent InventoryChangedEvent;
	
	// Widgets
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> InventoryWidgetClass;
	UPROPERTY()
	class UInventoryWidget* InventoryWidget;
	
	TArray<UItemData*> ItemsArray;
	bool NeedReload = false;
	
// Functions
	bool IsRoomAvailable(UItemData *ItemData, int TopLeftIndex);
	FVector2D IndexToTile(int Index);
	int TileToIndex(FVector2D Tile);
	UItemData* GetItemAtIndex(int Index);
};
