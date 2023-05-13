// Fill out your copyright notice in the Description page of Project Settings.

#include "SampleHubActor.h"
#include "Engine/World.h"

// Sets default values
ASampleHubActor::ASampleHubActor()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve
  // performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASampleHubActor::BeginPlay()
{
  Super::BeginPlay();

  UWorld* world = GetWorld();
  if (world)
  {

    for (int i = 0; i < 10; ++i)
    {
      auto spawned = world->SpawnActor<ABaseSampleActor>(
          GeneratedClass,
          FTransform(FRotator::ZeroRotator, FVector(i * 100, 300.f, 300.f)));
      if (spawned)
      {
        FSampleData data;
        data.MovementType = EMovementType::CIRCLE;
        data.Amplitude = FMath::RandRange(100, 300);
        data.Frequency = FMath::RandRange(1, 5);
        spawned->SetData(data);
      }
    }

    for (int i = 0; i < 10; ++i)
    {
      auto transform = FTransform(FRotator::ZeroRotator, FVector(i * 100, 300.f, 700.f));
      auto spawned =
          world->SpawnActorDeferred<ABaseSampleActor>(GeneratedClass, transform);
      if (spawned)
      {
        FSampleData data;
        data.Color = FLinearColor::Gray;
        spawned->SetData(data);
        spawned->FinishSpawning(transform);
      }
    }


    for (const auto payload : SamplePayload)
    {
      auto spawned = world->SpawnActorDeferred<ABaseSampleActor>(
          payload.GeneratedClass, payload.InitialTransform);

      if (spawned)
      {
        spawned->SetData(payload.Data);
        spawned->FinishSpawning(payload.InitialTransform);
      }
    }

  }
}

// Called every frame
void ASampleHubActor::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}
