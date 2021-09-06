// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Unreal_RPG/Core/DamageTypes/Physical_DT.h"
#include "EnemyBase.generated.h"

UCLASS()
class UNREAL_RPG_API AEnemyBase : public ACharacterBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageType> DamageType = TSubclassOf<UDamageType>(UPhysical_DT::StaticClass());

	

};
