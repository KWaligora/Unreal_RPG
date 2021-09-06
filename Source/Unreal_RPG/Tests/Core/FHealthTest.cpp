// Fill out your copyright notice in the Description page of Project Settings.


#include "FHealthTest.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/PainCausingVolume.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Unreal_RPG/Characters/CharacterBase.h"
#include "Unreal_RPG/Core/HealthComponent.h"

AFHealthTest::AFHealthTest()
{
	TimeLimit = 5.0f;
}

void AFHealthTest::BeginPlay()
{
	Super::BeginPlay();
	
	// is Damage Volume and Character set
	if(DamageVolume && Character)
	{
		// Can I get HealthComponent
		HealthComponent = Character->GetHealthComponent();
		if(HealthComponent)
		{
			// Can I get controller
			AController* Controller = Character->GetController();
			if(Controller)
			{
				// Set destination
				DestinationLocation = DamageVolume->GetActorLocation();
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, DestinationLocation);
			}
			else
			{
				FinishTest(EFunctionalTestResult::Failed, FString("Controller nullptr"));
				UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
			}
		}
		else
		{
			FinishTest(EFunctionalTestResult::Failed, FString("Health component nullptr"));
			UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
		}
	}
	else
	{
		FinishTest(EFunctionalTestResult::Failed, FString("Not set Damage Volume or Character"));
		UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
	}
}

void AFHealthTest::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(HealthComponent->GetCurrentHealth() < HealthComponent->GetMaxHealth())
	{
		FinishTest(EFunctionalTestResult::Succeeded, FString("Damage applied"));
		UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
	}
}
