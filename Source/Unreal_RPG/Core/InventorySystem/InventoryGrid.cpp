// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGrid.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Unreal_RPG/Core/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Unreal_RPG/Characters/PlayerBase.h"

void UInventoryGrid::CreateGrid(FVector2D GridSize)
{
	if(GridBorder == nullptr) return;		
	
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
			UE_LOG(LogTemp, Warning, TEXT("work"));
		}
	}
}

void UInventoryGrid::Refresh()
{
	//GridCanvasPanel->ClearChildren();
}


