// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseSampleActor.generated.h"

UENUM(BlueprintType)
enum class EMovementType : uint8
{
  CIRCLE,
  NONE
};

USTRUCT(BlueprintType)
struct FMovementData
{
  GENERATED_USTRUCT_BODY()

  UPROPERTY(EditAnywhere, Category = "Movement")
  EMovementType MovementType = EMovementType::NONE;

  UPROPERTY(EditAnywhere, Category = "Movement")
  int32 Amplitude = 100;

  UPROPERTY(EditAnywhere, Category = "Movement")
  int32 Frequency = 2;

  UPROPERTY(EditAnywhere, Category = "Design")
  FLinearColor Color = FLinearColor::Black;
};

UCLASS()
class CPP2PROJECT_API ABaseSampleActor : public AActor
{
  GENERATED_BODY()

  public:
  // Sets default values for this actor's properties
  ABaseSampleActor();

  protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  UPROPERTY(VisibleAnywhere)
  UStaticMeshComponent* BaseMesh;

  UPROPERTY(EditAnywhere, Category = "Movement")
  FMovementData MovementData;

  UPROPERTY(EditAnywhere, Category = "Weapon")
  int32 weapon_num = 4;

  UPROPERTY(EditDefaultsOnly, Category = "Stat")
  int32 kills_count = 4;

  UPROPERTY(VisibleAnywhere, Category = "Health")
  float health = 32.34234;

  UPROPERTY(EditInstanceOnly, Category = "Health")
  bool is_dead = false;

  UPROPERTY(EditInstanceOnly, Category = "Weapon")
  bool has_weapon = false;

  public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  private:
  FVector InitialLocation;
  void HandleMovement();
  void PrintTypes();
  void PrintStringTypes();
  void SetColor(const FLinearColor& color);
};
