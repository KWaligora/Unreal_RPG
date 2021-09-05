// Fill out your copyright notice in the Description page of Project Settings.


#include "RPG_PlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

ARPG_PlayerController::ARPG_PlayerController()
{
	bShowMouseCursor = true;
}

void ARPG_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ARPG_PlayerController::OnSetDestinationPressed);
}

void ARPG_PlayerController::OnSetDestinationPressed()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	if(HitResult.bBlockingHit)
	{
		MoveToLocation(HitResult.ImpactPoint);
	}
}

void ARPG_PlayerController::MoveToLocation(FVector Location)
{
	APawn* PlayerPawn = GetPawn();
	if(PlayerPawn)
	{		
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Location);
	}
}
