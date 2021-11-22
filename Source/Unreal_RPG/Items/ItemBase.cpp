// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "Components/BoxComponent.h"
#include "ItemData.h"
#include "Unreal_RPG/Characters/PlayerBase.h"
#include "Unreal_RPG/Core/InventoryComponent.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup components
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetupAttachment(StaticMesh);	
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnOverlap);

	if(ItemData == nullptr)
		ItemData = GetDefaultItem();
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Overlap event
void AItemBase::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	APlayerBase* Player = Cast<APlayerBase>(OtherActor);
	if(Player == nullptr) return;

	 UInventoryComponent* InventoryComponent =  Player->GetInventory();
	if(InventoryComponent != nullptr)
	{
		// If added successful, destroy item representation - item has been picked up 
		if(InventoryComponent->AddItem(ItemData))
		{
			Destroy();
		}
	}
}


