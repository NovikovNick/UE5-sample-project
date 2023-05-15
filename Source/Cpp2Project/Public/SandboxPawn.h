// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SandboxPawn.generated.h"

class UCameraComponent;

UCLASS()
class CPP2PROJECT_API ASandboxPawn : public APawn
{
  GENERATED_BODY()

  public:
  // Sets default values for this pawn's properties
  ASandboxPawn();

  UPROPERTY(EditAnywhere)
  USceneComponent* SceneComponent;

  UPROPERTY(EditAnywhere)
  float Velocity = 300.f;

  UPROPERTY(VisibleAnywhere)
  UStaticMeshComponent* Mesh;

  UPROPERTY(VisibleAnywhere)
  UCameraComponent* Camera;



  protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  virtual void PossessedBy(AController* controller) override;
  virtual void UnPossessed() override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(
      class UInputComponent* PlayerInputComponent) override;

  private:
  FVector VelocityVector = FVector::ZeroVector;
  void MoveForward(float Amount);
  void MoveRight(float Amount);
};
