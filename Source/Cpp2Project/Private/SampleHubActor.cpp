// Fill out your copyright notice in the Description page of Project Settings.

#include "SampleHubActor.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogSampleHub, Display, All)

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

  SpawnSamplePayload();
  // Spawn1();
  // Spawn2();
}

// Called every frame
void ASampleHubActor::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}

void ASampleHubActor::SpawnSamplePayload()
{
  UWorld* w = GetWorld();
  if (w)
  {
    for (const auto payload : SamplePayload)
    {
      auto spawned = w->SpawnActorDeferred<ABaseSampleActor>(payload.GeneratedClass,
                                                             payload.InitialTransform);

      if (spawned)
      {
        spawned->SetData(payload.Data);
        spawned->OnColorChanged.AddDynamic(this, &ASampleHubActor::OnColorChanged);
        spawned->OnTimeFinished.AddUObject(this, &ASampleHubActor::OnTimeFinished);
        spawned->FinishSpawning(payload.InitialTransform);
      }
    }
  }
}

void ASampleHubActor::Spawn1()
{
  UWorld* w = GetWorld();
  if (w)
  {
    for (int i = 0; i < 10; ++i)
    {
      auto transform = FTransform(FRotator::ZeroRotator, FVector(i * 100, 300.f, 300.f));
      auto spawned = w->SpawnActor<ABaseSampleActor>(GeneratedClass, transform);
      if (spawned)
      {
        FSampleData data;
        data.MovementType = EMovementType::CIRCLE;
        data.Amplitude = FMath::RandRange(100, 300);
        data.Frequency = FMath::RandRange(1, 5);
        spawned->SetData(data);
      }
    }
  }
}

void ASampleHubActor::Spawn2()
{
  UWorld* w = GetWorld();
  if (w)
  {
    for (int i = 0; i < 10; ++i)
    {
      auto transform = FTransform(FRotator::ZeroRotator, FVector(i * 100, 300.f, 700.f));
      auto spawned = w->SpawnActorDeferred<ABaseSampleActor>(GeneratedClass, transform);
      if (spawned)
      {
        FSampleData data;
        data.Color = FLinearColor::Gray;
        spawned->SetData(data);
        spawned->FinishSpawning(transform);
      }
    }
  }
}

void ASampleHubActor::OnColorChanged(const FLinearColor& Color, const FString& Name)
{
  UE_LOG(LogSampleHub, Error, TEXT("Color changed for %s"), *Name);
}

void ASampleHubActor::OnTimeFinished(AActor* Actor)
{
  if (!Actor) return;
  UE_LOG(LogSampleHub, Error, TEXT("Time finished %s"), *Actor->GetName());

  ABaseSampleActor* SampleActor = Cast<ABaseSampleActor>(Actor);
  if (!SampleActor) return;

  SampleActor->Destroy();
  // SampleActor->SetLifeSpan(2.0f);

}
