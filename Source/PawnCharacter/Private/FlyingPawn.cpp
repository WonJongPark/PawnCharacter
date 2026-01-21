#include "FlyingPawn.h"

#include "EnhancedInputComponent.h"
#include "MyPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

AFlyingPawn::AFlyingPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComp->SetSimulatePhysics(false);
	SetRootComponent(CapsuleComp);
	
	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowComp->SetSimulatePhysics(false);
	ArrowComp->SetupAttachment(RootComponent);
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkeletalMesh"));
	StaticMeshComp->SetSimulatePhysics(false);
	StaticMeshComp->SetupAttachment(RootComponent);
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 500.f;
	SpringArmComp->bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;
	
	MoveSpeed = 10.0f;
}

void AFlyingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFlyingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFlyingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
					&AFlyingPawn::Move);
			}
			
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AFlyingPawn::Look);
			}
			
			if (PlayerController->UpDownAction)
			{
				EnhancedInput->BindAction(
					PlayerController->UpDownAction,
					ETriggerEvent::Triggered,
					this,
					&AFlyingPawn::UpDown);
			}
			
			if (PlayerController->RollAction)
			{
				EnhancedInput->BindAction(
					PlayerController->RollAction,
					ETriggerEvent::Triggered,
					this,
					&AFlyingPawn::Roll);
			}
		}
	}
}

void AFlyingPawn::Move(const FInputActionValue& Value)
{
	if (!Controller) return;
	
	FVector2D MoveInput = Value.Get<FVector2D>();
	
	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		FVector DeltaLocation(MoveInput.X * MoveSpeed, 0.f, 0.f);
		AddActorLocalOffset(DeltaLocation);
	}
	
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		FVector DeltaLocation(0.f, MoveInput.Y * MoveSpeed, 0.f);
		AddActorLocalOffset(DeltaLocation);
	}
}

void AFlyingPawn::Look(const FInputActionValue& Value)
{
}

void AFlyingPawn::UpDown(const FInputActionValue& Value)
{
	if (!Controller) return;
	
	FVector2D MoveInput = Value.Get<FVector2D>();
	
	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		FVector DeltaLocation(0.f, 0.f, MoveInput.X * MoveSpeed);
		AddActorLocalOffset(DeltaLocation);
	}
}

void AFlyingPawn::Roll(const FInputActionValue& Value)
{
}

