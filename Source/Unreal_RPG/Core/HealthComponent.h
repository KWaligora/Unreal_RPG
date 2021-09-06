// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_RPG_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	DECLARE_EVENT( UHealthComponent, FDeathEvent )
	FDeathEvent& OnDeath() { return DeathEvent; }
	
	// Sets default values for this component's properties
	UHealthComponent();
	float GetCurrentHealth();
	float GetMaxHealth();
	UFUNCTION(BlueprintPure)
	bool IsOwnerAlive() const;

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	FDeathEvent DeathEvent;
	
	// Variables
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.0f;
	float CurrentHealth;
	bool IsAlive = true;
};
