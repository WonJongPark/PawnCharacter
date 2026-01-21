#include "ThirdPersonPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "MyPlayerController.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"

AThirdPersonPawn::AThirdPersonPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComp->SetSimulatePhysics(false);
	SetRootComponent(CapsuleComp);
	
	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowComp->SetSimulatePhysics(false);
	ArrowComp->SetupAttachment(RootComponent);
	
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComp->SetSimulatePhysics(false);
	SkeletalMeshComp->SetupAttachment(RootComponent);
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 200.f;
	SpringArmComp->bUsePawnControlRotation = false;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;
	
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
}

void AThirdPersonPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AThirdPersonPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// 1. 현재 폰의 속도를 가져옵니다.
	FVector Velocity = GetVelocity();

	// 2. 폰이 움직이고 있는지 확인합니다 (속도가 0에 가깝지 않다면)
	if (!Velocity.IsNearlyZero())
	{
		FRotator TargetRotation = Velocity.Rotation();
		
		TargetRotation.Pitch = 0.0f;
		TargetRotation.Roll = 0.0f;
		
		FRotator CurrentRotation = GetActorRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 10.0f);
		
		SetActorRotation(NewRotation);
	}
}

void AThirdPersonPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (const AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AThirdPersonPawn::Move);
			}
			
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AThirdPersonPawn::Look);
			}
		}
	}
}

void AThirdPersonPawn::Move(const FInputActionValue& Value)
{
	if (!Controller) return;
	
	const FVector2D MoveInput = Value.Get<FVector2D>();
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(ForwardDirection, MoveInput.X);
	}
	
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(RightDirection, MoveInput.Y);
	}
}

void AThirdPersonPawn::Look(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();
	
	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

