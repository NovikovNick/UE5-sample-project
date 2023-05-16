// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSampleActor.h"
#include "SampleHubActor.generated.h"

class UStaticMeshComponent;

USTRUCT(BlueprintType)
struct FSamplePayload
{
  GENERATED_USTRUCT_BODY()

  UPROPERTY(EditAnywhere)
  TSubclassOf<ABaseSampleActor> GeneratedClass;

  UPROPERTY(EditAnywhere)
  FSampleData Data;

  UPROPERTY(EditAnywhere)
  FTransform InitialTransform;
};

UCLASS()
class CPP2PROJECT_API ASampleHubActor : public AActor
{
  GENERATED_BODY()

  public:
  // Sets default values for this actor's properties
  ASampleHubActor();

  protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  protected:
  UPROPERTY(EditAnywhere)
  TSubclassOf<ABaseSampleActor> GeneratedClass;

  UPROPERTY(EditAnywhere)
  UClass* SomeClass;

  UPROPERTY(EditAnywhere)
  ABaseSampleActor* SampleObject;

  UPROPERTY(EditAnywhere)
  TArray<FSamplePayload> SamplePayload;

  private:
  void SpawnSamplePayload();
  void Spawn1();
  void Spawn2();

  UFUNCTION()
  void OnColorChanged(const FLinearColor& Color, const FString& Name);

  void OnTimeFinished(AActor* Actor);
};
