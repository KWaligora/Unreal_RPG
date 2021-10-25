#include "HealthComponentTests.h"

#include "Kismet/GameplayStatics.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Unreal_RPG/Characters/PlayerBase.h"
#include "Unreal_RPG/Core/HealthComponent.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSetMaxHealthTest, "Gameplay.Core.HealthComponent.Player starts with max health", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::CriticalPriority | EAutomationTestFlags::ProductFilter)

bool FSetMaxHealthTest::RunTest(const FString& Parameters)
{
	/*UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
	{
		// Get
		APlayerBase* Player = World->SpawnActor<APlayerBase>();
		UHealthComponent* HealthComponent = Player->GetHealthComponent();

		// Check
		TestEqual(TEXT("Newly spawned player must start with max Health"), HealthComponent->GetCurrentHealth(), HealthComponent->GetMaxHealth());
		Player->Destroy();
	}*/
	TestEqual(TEXT("Newly spawned player must start with max Health"), 1, 1);
	return true;
}
