// Copyright Epic Games, Inc. All Rights Reserved.

#include "Cpp2ProjectGameModeBase.h"
#include "SandboxPawn.h"
#include "SandboxPlayerController.h"

ACpp2ProjectGameModeBase::ACpp2ProjectGameModeBase()
{

  DefaultPawnClass = ASandboxPawn::StaticClass();
  PlayerControllerClass = ASandboxPlayerController::StaticClass();
}
