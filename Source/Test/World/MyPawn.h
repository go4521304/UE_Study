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

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* MyCapsule;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MyMesh;

	UPROPERTY(VisibleAnywhere)
	class UMyPawnMovementComponent* MyMovementComp;

	//UPROPERTY()
	//class USpringArmComponent* MySpringArmComp;

	//UPROPERTY()
	//class UCameraComponent* MyCam;

	UPROPERTY(EditDefaultsOnly)
	class UCameraActorComponent* MyCameraComponent;
	

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* MyName;

	UPROPERTY(EditAnywhere)
	class UDataTable* Table;


	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);

	UPROPERTY(ReplicatedUsing=OnRep_ChangePlayerId)
	FString PlayerID;

	UFUNCTION()
	void OnRep_ChangePlayerId();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Client, Reliable)
	void ClientInitSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetPlayerId(const FString& NewPlayerId);

	virtual void PostNetInit() override;
};
