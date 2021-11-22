// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

#include "InventoryGrid.h"
#include "Blueprint/DragDropOperation.h"
#include "Unreal_RPG/Items/ItemData.h"
#include "Unreal_RPG/Items/ItemBase.h"

bool UInventoryWidget::NativeOnDrop(const FGeometry& MovieSceneBlends, const FDragDropEvent& InDragDropEvent,
                                    UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(MovieSceneBlends, InDragDropEvent, InOperation);
	
	if(InOperation == nullptr) return false;
	UItemData* ItemData = Cast<UItemData>(InOperation->Payload);
	if(ItemData == nullptr) return false;
	
	UWorld* World = GetWorld();
	if(World == nullptr) return false;

	TSubclassOf<AItemBase> ItemClass = ItemData->GetItemClass();	
	AActor* Item = World->SpawnActor(ItemClass);
	if(Item == nullptr) return false;
	
	FVector DropItemLocation = GetOwningPlayerPawn()->GetActorLocation() + GetOwningPlayerPawn()->GetActorForwardVector() * 200;	
	Item->SetActorLocation(DropItemLocation);	
	
	return true;
}

void UInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(WPB_InventoryGrid == nullptr) return;

	WPB_InventoryGrid->CreateGrid(FVector2D(GridSize));
}
