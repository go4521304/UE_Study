// Copyright Epic Games, Inc. All Rights Reserved.

#include "OtakuCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AOtakuCharacter

AOtakuCharacter::AOtakuCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	WeaponMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMeshComp"));
	WeaponMeshComp->SetupAttachment(GetMesh());

	bFocusMode = false;

	WalkSpeed = 230.0f;

}

void AOtakuCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	USkeletalMesh* WeaponMesh = WeaponMeshPath.LoadSynchronous();
	if (IsValid(WeaponMesh))
	{
		WeaponMeshComp->SetSkeletalMesh(WeaponMesh);
		WeaponMeshComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Weapon"));
	}

}

//////////////////////////////////////////////////////////////////////////
// Input

void AOtakuCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOtakuCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AOtakuCharacter::Look);

		// Walk
		EnhancedInputComponent->BindAction(WalkAction, ETriggerEvent::Triggered, this, &AOtakuCharacter::Walk);

		// Focus
		TSoftObjectPtr<UInputAction> FocusActionPtr;
		FocusActionPtr = FSoftObjectPath(TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Focus.IA_Focus'"));
		FocusActionPtr.LoadSynchronous();
		if (FocusActionPtr.IsValid())
		{
			EnhancedInputComponent->BindAction(FocusActionPtr.Get(), ETriggerEvent::Triggered, this, &AOtakuCharacter::EnemyFocus);
		}

		// Attack
		TSoftObjectPtr<UInputAction> AttackActionPtr;
		AttackActionPtr = FSoftObjectPath(TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Attack.IA_Attack'"));
		AttackActionPtr.LoadSynchronous();
		if (AttackActionPtr.IsValid())
		{
			EnhancedInputComponent->BindAction(AttackActionPtr.Get(), ETriggerEvent::Triggered, this, &AOtakuCharacter::Attack);
		}
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AOtakuCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (IsValid(GetCharacterMovement()))
	{
		float CharaVel = GetCharacterMovement()->Velocity.Size2D();
		if (3.0f < CharaVel)
		{
			if (bFocusMode)
			{
				FRotator CurRotation = FRotator::ZeroRotator;
				CurRotation.Yaw = GetActorRotation().Yaw;

				FRotator TargetRotation = FRotator::ZeroRotator;
				TargetRotation.Yaw = GetControlRotation().Yaw;

				float RotationSpeed = GetCharacterMovement()->RotationRate.Yaw;
				FRotator DestRotation = FMath::RInterpConstantTo(CurRotation, TargetRotation, DeltaSeconds, RotationSpeed);
				SetActorRotation(DestRotation.Quaternion());
			}
			else
			{
				FRotator CurRotation = FRotator::ZeroRotator;
				CurRotation.Yaw = GetActorRotation().Yaw;

				FVector VelVec = GetCharacterMovement()->Velocity.GetSafeNormal2D();
				FRotator VelRot = VelVec.ToOrientationRotator();
				VelRot.Pitch = 0.0f;
				VelRot.Roll = 0.0f;
 
				float RotationSpeed = GetCharacterMovement()->RotationRate.Yaw;
				FRotator DestRotation = FMath::RInterpConstantTo(CurRotation, VelRot, DeltaSeconds, RotationSpeed);
				SetActorRotation(DestRotation.Quaternion());
			}
		}
	}
}

void AOtakuCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AOtakuCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AOtakuCharacter::Walk(const FInputActionValue& Value)
{
	bool bWalking = Value.Get<bool>();

	if (bWalking)
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	}
}

void AOtakuCharacter::EnemyFocus(const FInputActionValue& Value)
{
	bool bTrigger = Value.Get<bool>();
	if (bTrigger)
	{
		bFocusMode = !bFocusMode;

		if (bFocusMode)
		{
			FRotator FocusRotation = GetActorRotation();
			FocusRotation.Pitch = -10.0f;
			FocusRotation.Roll = 0.0f;
			GetController()->SetControlRotation(FocusRotation);
		}
	}
}

void AOtakuCharacter::Attack(const FInputActionValue& Value)
{
	if (bFocusMode == false)
	{
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("Attack!"));
}
