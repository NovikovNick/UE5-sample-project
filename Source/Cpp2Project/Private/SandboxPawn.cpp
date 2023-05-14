// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxPawn.h"
#include "Components/InputComponent.h"

// Sets default values
ASandboxPawn::ASandboxPawn()
{
  // Set this pawn to call Tick() every frame.  You can turn this off to improve
  // performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  SceneComponent = CreateDefaultSubobject<USceneComponent>("USceneComponent");
  SetRootComponent(SceneComponent);
}

// Called when the game starts or when spawned
void ASandboxPawn::BeginPlay()
{
  Super::BeginPlay();
}

// Called every frame
void ASandboxPawn::Tick(float dx)
{
  Super::Tick(dx);

  if (!VelocityVector.IsZero())
  {
    const FVector newPosition = GetActorLocation() + Velocity * dx * VelocityVector;
    SetActorLocation(newPosition);
  }
}

// Called to bind functionality to input
void ASandboxPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  PlayerInputComponent->BindAxis("MoveForward", this, &ASandboxPawn::MoveForward);
  PlayerInputComponent->BindAxis("MoveRight", this, &ASandboxPawn::MoveRight);
}

void ASandboxPawn::MoveForward(float Amount)
{
  VelocityVector.X = Amount;
}

void ASandboxPawn::MoveRight(float Amount)
{
  VelocityVector.Y = Amount;
}
