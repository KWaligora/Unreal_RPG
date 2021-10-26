// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_RPG_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

// Variables
	bool bIsOpened = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// Show/Hide inventory
	void ToggleInventoryWidget();
	
private:
// Variables
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> InventoryWidgetClass;
	UPROPERTY()
	UUserWidget* InventoryWidget;
};
