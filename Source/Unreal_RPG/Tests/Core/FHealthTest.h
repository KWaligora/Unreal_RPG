// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "FHealthTest.generated.h"

class ACharacterBase;
class APainCausingVolume;
class UHealthComponent;

UCLASS()
class UNREAL_RPG_API AFHealthTest : public AFunctionalTest
{
	GENERATED_BODY()

	AFHealthTest();
	
	protected:

	UPROPERTY(EditAnywhere, Category="Test Data")
	ACharacterBase* Character;

	UPROPERTY(EditAnywhere, Category="Test Data")
	APainCausingVolume* DamageVolume;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	FVector DestinationLocation;
	
	UPROPERTY()
	UHealthComponent* HealthComponent;
};
