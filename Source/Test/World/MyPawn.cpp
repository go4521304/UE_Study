// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "MyPawnMovementComponent.h"
#include "Components/InputComponent.h"
#include "CameraActorComponent.h"
#include "Components/WidgetComponent.h"
#include "IconTable.h"
#include "WorldPlayerState.h"
#include "WorldGameStateBase.h"
#include "Net/UnrealNetwork.h"
#include "IdUserWidget.h"


// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	MyMovementComp = CreateDefaultSubobject<UMyPawnMovementComponent>(TEXT("MovementmentComponent"));
	//MySpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	//MyCam = CreateDefaultSubobject<UCameraComponent>(TEXT("Cam"));

	SetRootComponent(MyCapsule);
	MyMesh->SetupAttachment(GetRootComponent());
	//MySpringArmComp->SetupAttachment(GetRootComponent());
	//MyCam->SetupAttachment(MySpringArmComp);

	MyCameraComponent = CreateDefaultSubobject<UCameraActorComponent>(TEXT("Cam"));
	MyCameraComponent->SetupAttachment(GetRootComponent());
	//MyCameraComponent->SpringArm->SetupAttachment(GetRootComponent());
	//MyCameraComponent->Camera->SetupAttachment(MyCameraComponent->SpringArm);

	SetActorLocation(FVector(0.f, 0.f, -30.f));

	MyCapsule->InitCapsuleSize(22.f, 44.f);
	MyCapsule->SetCollisionProfileName(TEXT("Pawn"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ChairMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'"));
	if (ChairMeshAsset.Succeeded())
	{
		MyMesh->SetStaticMesh(ChairMeshAsset.Object);
	}
	MyMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -30.f));
	MyMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	MyName = CreateDefaultSubobject<UWidgetComponent>(TEXT("Name"));
	MyName->SetDrawAtDesiredSize(true);
	MyName->SetWidgetSpace(EWidgetSpace::Screen);
	MyName->SetupAttachment(GetRootComponent());

	MyMovementComp->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Error, TEXT("BeginPlay"));

	if (!IsValid(MyName->GetWidget()))
	{
		return;
	}

	UIdUserWidget* IDWidget = Cast<UIdUserWidget>(MyName->GetWidget());
	if (!IsValid(IDWidget) || PlayerID.IsEmpty())
	{
		return;
	}

	IDWidget->SetPlayerId(PlayerID);
}

void AMyPawn::OnRep_ChangePlayerId()
{
	if (!IsValid(MyName->GetWidget()))
	{
		return;
	}

	UIdUserWidget* IDWidget = Cast<UIdUserWidget>(MyName->GetWidget());
	if (!IsValid(IDWidget) || PlayerID.IsEmpty())
	{
		return;
	}

	IDWidget->SetPlayerId(PlayerID);
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	InputComponent->BindAxis("MoveForward", this, &AMyPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPawn::MoveRight);
	InputComponent->BindAxis("Turn Right / Left Mouse", this, &AMyPawn::Turn);
}

void AMyPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPawn, PlayerID);
}

void AMyPawn::SetPlayerId(const FString& NewPlayerId)
{
	PlayerID = NewPlayerId;
	UE_LOG(LogTemp, Error, TEXT("SetPlayerID: %s"), *PlayerID);

	if (!IsValid(MyName->GetWidget()))
	{
		return;
	}

	UIdUserWidget* IDWidget = Cast<UIdUserWidget>(MyName->GetWidget());
	if (!IsValid(IDWidget) || PlayerID.IsEmpty())
	{
		return;
	}

	IDWidget->SetPlayerId(PlayerID);
}


void AMyPawn::PostNetInit()
{
	Super::PostNetInit();
	UE_LOG(LogTemp, Error, TEXT("PostNetInit: %s"), *PlayerID);
}

void AMyPawn::ClientInitSet_Implementation()
{
	if (IsValid(GetWorld()->GetGameState()))
	{
		UE_LOG(LogTemp, Error, TEXT("check GameState"));
	}
	if (IsValid(MyName->GetWidget()))
	{
		UE_LOG(LogTemp, Error, TEXT("check Widget"));
	}
}

void AMyPawn::MoveForward(float AxisValue)
{
	if (MyMovementComp && MyMovementComp->UpdatedComponent == RootComponent)
	{
		MyMovementComp->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void AMyPawn::MoveRight(float AxisValue)
{
	if (MyMovementComp && MyMovementComp->UpdatedComponent == RootComponent)
	{
		MyMovementComp->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

void AMyPawn::Turn(float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
}
