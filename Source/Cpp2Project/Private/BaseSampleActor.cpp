// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseSampleActor.h"

#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Engine.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogSample, Display, All)

// Sets default values
ABaseSampleActor::ABaseSampleActor()
{
  // Set this actor to call Tick() every frame.  You can turn this off to
  // improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
  BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base component");
  SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ABaseSampleActor::BeginPlay()
{
  Super::BeginPlay();
  InitialLocation = GetActorLocation();

  SetColor(Data.Color);

  GetWorldTimerManager().SetTimer(
      TimerHandler, this, &ABaseSampleActor::OnTimerFired, Data.TimerRate, true);
  // printStringTypes();
  // PrintTypes();
}

// Called every frame
void ABaseSampleActor::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  HandleMovement();
}

void ABaseSampleActor::HandleMovement()
{
  switch (Data.MovementType)
  {
    case EMovementType::CIRCLE:
    {
      FTransform transform = GetTransform();
      auto location = transform.GetLocation();

      auto time = GetWorld()->GetTimeSeconds();
      location.Z = InitialLocation.Z + Data.Amplitude * FMath::Sin(time * Data.Frequency);
      location.X = InitialLocation.X + Data.Amplitude * FMath::Cos(time * Data.Frequency);
      SetActorLocation(location);
    }
  }
}

void ABaseSampleActor::PrintTypes()
{
  UE_LOG(LogSample, Display, TEXT("Actor name: %s"), *GetName());
  UE_LOG(LogSample, Display, TEXT("weapons: %d"), weapon_num);
  UE_LOG(LogSample, Display, TEXT("kills: %i"), kills_count);
  UE_LOG(LogSample, Display, TEXT("Health: %f"), health);
  UE_LOG(LogSample, Display, TEXT("Dead: %d"), is_dead);
  UE_LOG(LogSample, Display, TEXT("Has weapon: %d"), has_weapon);
}

void ABaseSampleActor::PrintStringTypes()
{
  FString weapon_str = "Weapon = " + FString::FromInt(weapon_num);
  FString kills_str = "Kills = " + FString::FromInt(kills_count);
  FString health_str = "Health = " + FString::SanitizeFloat(health);
  FString dead_str = "Is dead = " + FString(is_dead ? "true" : "false");

  FString stat_str = FString::Printf(TEXT(" \n -- All stats -- \n %s\n %s\n %s\n %s\n"),
                                     *weapon_str,
                                     *kills_str,
                                     *health_str,
                                     *dead_str);
  UE_LOG(LogSample, Warning, TEXT("%s"), *stat_str);

  GEngine->AddOnScreenDebugMessage(
      -1, 5.0f, FColor::Cyan, stat_str, true, FVector2D(1.f, 1.f));
}

void ABaseSampleActor::SetColor(const FLinearColor& color)
{
  if (!BaseMesh) return;

  UMaterialInstanceDynamic* DynMaterial =
      BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
  if (DynMaterial)
  {
    DynMaterial->SetVectorParameterValue("color", color);
  }
}

void ABaseSampleActor::OnTimerFired()
{
  if (++CurrTimerCount <= MaxTimerCount)
  {
    FLinearColor newColor = FLinearColor::MakeRandomColor();
    SetColor(newColor);
    UE_LOG(LogSample,
           Warning,
           TEXT("%d# Color changed %s"),
           CurrTimerCount,
           *newColor.ToString());
  }
}
