// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

class UItemData;

UCLASS()
class UNREAL_RPG_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Overlap event
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// Components
	UPROPERTY(EditDefaultsOnly, Category="Components")
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditDefaultsOnly, Category="Components")
	class UBoxComponent* BoxComponent;	

	UPROPERTY()
	UItemData* ItemData;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DeterminesOutputType="Parameter"))
	UItemData* GetDefaultItem();	
};
