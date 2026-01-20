#include "ThirdPersonPawn.h"

AThirdPersonPawn::AThirdPersonPawn()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AThirdPersonPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AThirdPersonPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AThirdPersonPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

