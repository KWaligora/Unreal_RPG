// Fill out your copyright notice in the Description page of Project Settings.


#include "RPG_PlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

ARPG_PlayerController::ARPG_PlayerController()
{
	bShowMouseCursor = true;
}

void ARPG_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(bMoving)
	{
		SetNewDestination();
	}		
}

void ARPG_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ARPG_PlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ARPG_PlayerController::OnSetDestinationReleased);
}
// Calculate new destination and call MoveToLocation
void ARPG_PlayerController::SetNewDestination()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	if(HitResult.bBlockingHit)
	{
		MoveToLocation(HitResult.ImpactPoint);
	}
}

// if player click on map, set this location as destination
void ARPG_PlayerController::OnSetDestinationPressed()
{
	bMoving = true;
}

void ARPG_PlayerController::OnSetDestinationReleased()
{
	bMoving = false;
}

void ARPG_PlayerController::MoveToLocation(FVector Location)
{
	APawn* PlayerPawn = GetPawn();
	if(PlayerPawn)
	{		
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Location);
	}
}
