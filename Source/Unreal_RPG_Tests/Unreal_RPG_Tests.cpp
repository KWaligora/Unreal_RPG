// Fill out your copyright notice in the Description page of Project Settings.

#include "Unreal_RPG_Tests.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"

IMPLEMENT_GAME_MODULE(FUnreal_RPG_TestsModule, Unreal_RPG_Tests);

DEFINE_LOG_CATEGORY(Unreal_RPG_Tests)

#define LOCTEXT_NAMESPACE "Unreal_RPG_Tests"

void FUnreal_RPG_TestsModule::StartupModule()
{
	UE_LOG(Unreal_RPG_Tests, Warning, TEXT("Tests: Log Started"));
}

void FUnreal_RPG_TestsModule::ShutdownModule()
{
	UE_LOG(Unreal_RPG_Tests, Warning, TEXT("Tests: Log Ended"));
}

#undef LOCTEXT_NAMESPACE

