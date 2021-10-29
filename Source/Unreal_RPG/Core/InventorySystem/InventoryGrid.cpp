// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGrid.h"

#include "ItemWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Unreal_RPG/Core/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Unreal_RPG/Characters/PlayerBase.h"


UInventoryGrid::UInventoryGrid(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{	
	ConstructorHelpers::FClassFinder<UUserWidget> ItemWidgetBPClass(TEXT("/Game/UI/Inventory/WBP_Item"));
	if(!ensure(ItemWidgetBPClass.Class != nullptr)) return;

	ItemWidgetClass = ItemWidgetBPClass.Class;
}

void UInventoryGrid::CreateGrid(FVector2D GridSize)
{
	if(GridBorder == nullptr || InventoryComponent == nullptr) return;		
	
	UCanvasPanelSlot* GridBorderSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot);
	GridBorderSlot->SetSize(GridSize * TileSize);

	// Vertical Lines
	for(int i = 0; i < GridSize.X; i++)
	{		
		float LineX = i * TileSize;
		Lines.Add(FVector4(LineX, 0, LineX, TileSize * GridSize.Y));
	}
	// Horizontal lines
	for(int i = 0; i<GridSize.Y; i++)
	{
		float LineY = i*TileSize;
		Lines.Add(FVector4(0.0, LineY, TileSize * GridSize.X, LineY));
	}
	Refresh();
	InventoryComponent->OnInventoryChanged().AddUObject(this, &UInventoryGrid::Refresh);
}
// Called by blueprint OnPaint event
void UInventoryGrid::Paint(FPaintContext Context) const
{	
	if(GridBorder == nullptr) return;
	
	FVector2D LocalTopLeft = GridBorder->GetCachedGeometry().GetLocalPositionAtCoordinates(FVector2D(0,0));
	for (FVector4 Line : Lines)
	{
		UWidgetBlueprintLibrary::DrawLine(Context, FVector2D(Line.X, Line.Y) + LocalTopLeft, FVector2D(Line.Z, Line.W) + LocalTopLeft, FLinearColor(0.5,0.5,0.5, 0.5));
	}	
}

// Getting inventory component
void UInventoryGrid::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	TArray<AActor*> Actors;
	TSubclassOf<APlayerBase> PlayerClass = APlayerBase::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerClass, Actors);
	for (AActor* Actor : Actors)
	{
		APlayerBase* PlayerBase = Cast<APlayerBase>(Actor);
		if(PlayerBase != nullptr)
		{
			InventoryComponent = PlayerBase->GetInventory();
		}
	}
	
	ItemsWidget.SetNum(100);	
}

void UInventoryGrid::Refresh()
{
	if(InventoryComponent == nullptr || GridCanvasPanel == nullptr) return;
	
	GridCanvasPanel->ClearChildren();
	TMap<UItemData*, FVector2D> AllItems = InventoryComponent->GetAllItems();
	
	TArray<UItemData*> MapKeys;
	AllItems.GetKeys(MapKeys);
	
	int Index = 0;
	// Create Widget for every item in inventory
	for(UItemData* Key : MapKeys)
	{
		ItemsWidget[Index] = Cast<UItemWidget>(CreateWidget(GetWorld()->GetFirstPlayerController(), ItemWidgetClass));
		ItemsWidget[Index]->Initialise(TileSize, Key);	
		ItemsWidget[Index]->OnRemove().AddUObject(this, &UInventoryGrid::OnItemRemoved);
		if(UPanelSlot* PanelSlot = GridCanvasPanel->AddChild(ItemsWidget[Index]))
		{
			if(UCanvasPanelSlot* ChildSlot = Cast<UCanvasPanelSlot>(PanelSlot))
			{
				ChildSlot->SetAutoSize(true);
				ChildSlot->SetPosition(AllItems[Key] * TileSize);
			}
		}		
		Index++;
	}
}

void UInventoryGrid::OnItemRemoved(UItemData* ItemData)
{
	InventoryComponent->RemoveItem(ItemData);
}
