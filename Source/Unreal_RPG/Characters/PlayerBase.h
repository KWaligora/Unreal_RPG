// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "PlayerBase.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class UNREAL_RPG_API APlayerBase : public ACharacterBase
{
	GENERATED_BODY()

	public:
	// Sets default values for this character's properties
	APlayerBase();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Components
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
	
};
