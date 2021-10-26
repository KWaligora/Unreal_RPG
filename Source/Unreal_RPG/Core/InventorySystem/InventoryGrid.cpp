// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGrid.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Border.h"

void UInventoryGrid::CreateGrid(FVector2D GridSize)
{
	if(GridBorder == nullptr) return;		
	
	GridBorder->SetDesiredSizeScale( GridSize * TileSize);

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

void UInventoryGrid::Paint(FPaintContext Context) const
{	
	if(GridBorder == nullptr) return;
	
	FVector2D LocalTopLeft = GridBorder->GetCachedGeometry().GetLocalPositionAtCoordinates(FVector2D(0,0));
	for (FVector4 Line : Lines)
	{
		UE_LOG(LogTemp, Warning, TEXT("ver"));
		UWidgetBlueprintLibrary::DrawLine(Context, FVector2D(Line.X, Line.Y) + LocalTopLeft, FVector2D(Line.Z, Line.W) + LocalTopLeft, FLinearColor(0.5,0.5,0.5, 0.5));
	}	
}


