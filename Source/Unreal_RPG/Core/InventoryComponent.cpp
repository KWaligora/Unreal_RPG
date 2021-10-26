// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "InventorySystem/InventoryWidget.h"
#include "Blueprint/UserWidget.h"

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
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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

