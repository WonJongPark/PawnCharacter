// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonPawn.h"

// Sets default values
AThirdPersonPawn::AThirdPersonPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AThirdPersonPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThirdPersonPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AThirdPersonPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

