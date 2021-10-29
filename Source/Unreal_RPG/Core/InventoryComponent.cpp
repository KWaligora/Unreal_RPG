// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "InventorySystem/InventoryWidget.h"
#include "Blueprint/UserWidget.h"
#include "Unreal_RPG/Items/ItemData.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// Create InventoryWidget
	InventoryWidget = Cast<UInventoryWidget>(CreateWidget(GetWorld()->GetFirstPlayerController(), InventoryWidgetClass));
	if(InventoryWidget == nullptr) return;
	InventoryWidget->AddToViewport();
	InventoryWidget->SetVisibility(ESlateVisibility::Hidden);

	GridSize = InventoryWidget->GetGridSize();
	
	ItemsArray.SetNum(GridSize.X * GridSize.Y);
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(NeedReload)
	{
		NeedReload = false;	
		InventoryChangedEvent.Broadcast();
	}
}
// Show/Hide inventory
void UInventoryComponent::ToggleInventoryWidget()
{
	if(InventoryWidget == nullptr) return;
	
	// Open/Close
	if(!bIsOpened)
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		bIsOpened = true;
	}
	else
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		bIsOpened = false;
	}	
}

bool UInventoryComponent::AddItem(UItemData* ItemData )
{
	if(ItemData == nullptr) return false;

	int Index = 0;
	for (UItemData* Item : ItemsArray)
	{
		if(IsRoomAvailable(ItemData, Index))
		{
			FVector2D Tile = IndexToTile(Index);
			FVector2D ItemDimension = ItemData->GetDimensions();

			int end = Tile.X + ItemDimension.X;
			for (int i = Tile.X; i < end; i++)
			{
				for(int j = Tile.Y; j < Tile.Y + ItemDimension.Y; j++)
				{					
					int ItemArrayIndex =  TileToIndex(FVector2D(i,j));
					if(ItemsArray.IsValidIndex(ItemArrayIndex))
					{
						ItemsArray[ItemArrayIndex] = ItemData;
					}
				}
			}
			NeedReload = true;
			return true;
		}
		Index++;
	}	
	return false;
}

bool UInventoryComponent::IsRoomAvailable(UItemData *ItemData, int TopLeftIndex)
{
	FVector2D Tile = IndexToTile(TopLeftIndex);
	FVector2D ItemDimension = ItemData->GetDimensions();
	
	int end = Tile.X + ItemDimension.X;
	for (int i = Tile.X; i < end; i++)
	{
		for(int j = Tile.Y; j < Tile.Y + ItemDimension.Y; j++)
		{
			if(i >= 0 && j >= 0 && i < GridSize.X && j < GridSize.Y)
			{
				// Check if we found valid item at current index
				UItemData* Item = GetItemAtIndex(TileToIndex(FVector2D(i,j)));
				if(Item != nullptr)
				{
					return false;
				}
			}
			else return false;
		}
	}
	return true;
}

FVector2D UInventoryComponent::IndexToTile(int Index)
{
	if(InventoryWidget == nullptr) return FVector2D(0,0);	

	int Columns =  GridSize.X;
	int Rows = GridSize.Y;
	
	return FVector2D(Index % Columns, Index/Columns);
}

int UInventoryComponent::TileToIndex(FVector2D Tile)
{
	if(InventoryWidget == nullptr) return 0;	

	return Tile.X + Tile.Y * GridSize.X;
}

UItemData* UInventoryComponent::GetItemAtIndex(int Index)
{
	if( ItemsArray.IsValidIndex(Index))
	{		
		return ItemsArray[Index];
	}
	return nullptr;
}

TMap<UItemData*, FVector2D> UInventoryComponent::GetAllItems()
{
	TMap<UItemData*, FVector2D> AllItems;
	int index = 0;
	
	for (UItemData* ItemData : ItemsArray)
	{
		if(ItemData != nullptr && !AllItems.Contains(ItemData))
		{
			AllItems.Add(ItemData, IndexToTile(index));
		}
		index++;
	}
	return AllItems;
}

void UInventoryComponent::RemoveItem(UItemData* ItemData)
{
	
}
