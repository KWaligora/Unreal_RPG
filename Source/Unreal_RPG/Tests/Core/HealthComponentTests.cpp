// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponentTests.h"

#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Unreal_RPG/Characters/EnemyBase.h"
#include "Unreal_RPG/Characters/PlayerBase.h"
#include "Unreal_RPG/Core/HealthComponent.h"
#include "Unreal_RPG/Core/DamageTypes/Physical_DT.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSetMaxHealthTest, "Gameplay.Core.HealthComponent.Player starts with max health", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::CriticalPriority | EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FDealDamageTest, "Gameplay.Core.HealthComponent.Deal damage to player", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::CriticalPriority | EAutomationTestFlags::ProductFilter)

bool FSetMaxHealthTest::RunTest(const FString& Parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	{
		APlayerBase* Player = World->SpawnActor<APlayerBase>();
		UHealthComponent* HealthComponent = Player->GetHealthComponent();

		TestEqual(TEXT("Newly spawned player must start with max Health"), HealthComponent->GetCurrentHealth(), HealthComponent->GetMaxHealth());
		Player->Destroy();
	}
	return true;
}

bool FDealDamageTest::RunTest(const FString& Parameters)
{
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	{
		APlayerBase* Player = World->SpawnActor<APlayerBase>();
		UHealthComponent* HealthComponent = Player->GetHealthComponent();

		AEnemyBase* Enemy = World->SpawnActor<AEnemyBase>();

		TSubclassOf<UDamageType> DamageType = TSubclassOf<UDamageType>(UPhysical_DT::StaticClass());
		
		float ResultHealth = HealthComponent->GetCurrentHealth() - 20.0f;		
		TestEqual(TEXT("Damage calculation for 20 flat dmg"), HealthComponent->GetCurrentHealth(), ResultHealth);
	}
	return  true;
}

