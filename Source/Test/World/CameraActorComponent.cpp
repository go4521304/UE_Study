// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraActorComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values for this component's properties
UCameraActorComponent::UCameraActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(this);
	

	// Set the desired spring arm settings
	SpringArm->TargetArmLength = 500.f;
	SpringArm->bDoCollisionTest = true;
	//SetAbsolute(true, true, false);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// Set the desired camera settings
	Camera->FieldOfView = 90.f;
	Camera->AspectRatio = 16.f / 9.f;
}


// Called when the game starts
void UCameraActorComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
}

void UCameraActorComponent::OnRegister()
{
	Super::OnRegister();
	SpringArm->SetupAttachment(this);
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	UE_LOG(LogTemp, Warning, TEXT("OnRegister"));
}


// Called every frame
void UCameraActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

