// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "PlayerBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInventoryComponent;

UCLASS()
class UNREAL_RPG_API APlayerBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDeath() override;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	UInventoryComponent* GetInventory() { return Inventory; }

private:
	// Components
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere)
	UInventoryComponent* Inventory;


};
