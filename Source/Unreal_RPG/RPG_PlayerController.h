// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RPG_PlayerController.generated.h"

UCLASS()
class UNREAL_RPG_API ARPG_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARPG_PlayerController();
	virtual void Tick(float DeltaSeconds) override;
	

protected:
// Functions
	virtual void SetupInputComponent() override;
	
#pragma region Movement
	// Calculate new destination and call MoveToLocation
	void SetNewDestination();	
	// If player click on map, set this location as destination
	void OnSetDestinationPressed();
	// If player release mouse click stop calculating destination
	void OnSetDestinationReleased();
	// Move player to location
	void MoveToLocation(FVector Location);
	
	// Is player moving
	bool bMoving;
#pragma endregion Movement
};
