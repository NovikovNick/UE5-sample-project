// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxPawn.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPawn, Display, All)

// Sets default values
ASandboxPawn::ASandboxPawn()
{
  // Set this pawn to call Tick() every frame.  You can turn this off to improve
  // performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
  SetRootComponent(SceneComponent);

  Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
  Mesh->SetupAttachment(GetRootComponent());

  Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
  Camera->SetupAttachment(GetRootComponent());
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

  if (!VelocityVector.IsZero())  // && IsControlled()
  {
    const FVector newPosition = GetActorLocation() + Velocity * dx * VelocityVector;
    SetActorLocation(newPosition);
    VelocityVector = FVector::ZeroVector;
  }
}

void ASandboxPawn::PossessedBy(AController* NewController)
{
  Super::PossessedBy(NewController);
  UE_LOG(LogSandboxPawn, Warning, TEXT("%s possessed by controller"), *GetName());
}

void ASandboxPawn::UnPossessed()
{
  Super::UnPossessed();
  UE_LOG(LogSandboxPawn, Warning, TEXT("%s unpossessed"), *GetName());
}

// Called to bind functionality to input
void ASandboxPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);
  if (PlayerInputComponent)
  {
    PlayerInputComponent->BindAxis("MoveForward", this, &ASandboxPawn::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASandboxPawn::MoveRight);
  }
}

void ASandboxPawn::MoveForward(float Amount)
{
  VelocityVector.X = Amount;
}

void ASandboxPawn::MoveRight(float Amount)
{
  VelocityVector.Y = Amount;
}
