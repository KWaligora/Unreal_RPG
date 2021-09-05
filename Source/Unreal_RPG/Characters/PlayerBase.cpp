// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APlayerBase::APlayerBase()
{
	// Create Components
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
}
