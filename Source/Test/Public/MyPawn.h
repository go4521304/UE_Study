// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class TEST_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* MyCapsule;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MyMesh;

	UPROPERTY(VisibleAnywhere)
	class UMyPawnMovementComponent* MyMovementComp;

	UPROPERTY()
	class USpringArmComponent* MySpringArmComp;

	UPROPERTY()
	class UCameraComponent* MyCam;


	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
