// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "Unreal_RPG/Core/HealthComponent.h"

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// Bind Function to event	
	HealthComponent->OnDeath().AddUObject(this, &ACharacterBase::HandleDeath);
}

void ACharacterBase::HandleDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("CB"));
}

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Components
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UHealthComponent* ACharacterBase::GetHealthComponent()
{
	return HealthComponent;
}
