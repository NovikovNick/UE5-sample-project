// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxPlayerController.h"
#include "Components/InputComponent.h"
#include "SandboxPawn.h"

#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPlayerController, Display, All)

void ASandboxPlayerController::SetupInputComponent()
{
  Super::SetupInputComponent();
  InputComponent->BindAction(
      "ChangePawn", IE_Pressed, this, &ASandboxPlayerController::ChangePawn);
}

void ASandboxPlayerController::BeginPlay()
{
  Super::BeginPlay();
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandboxPawn::StaticClass(), Pawns);
}

void ASandboxPlayerController::ChangePawn()
{
  if (Pawns.Num() <= 1) return;

  CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Num();
  ASandboxPawn* CurrentPawn = Cast<ASandboxPawn>(Pawns[CurrentPawnIndex]);
  if (!CurrentPawn) return;

  Possess(CurrentPawn);

  UE_LOG(LogSandboxPlayerController, Warning, TEXT("Pawn changed!"));
}
