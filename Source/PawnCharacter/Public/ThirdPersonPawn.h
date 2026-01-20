#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ThirdPersonPawn.generated.h"

class UArrowComponent;
class UCameraComponent;
class USpringArmComponent;
class UCapsuleComponent;

UCLASS()
class PAWNCHARACTER_API AThirdPersonPawn : public APawn
{
	GENERATED_BODY()

public:
	AThirdPersonPawn();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCapsuleComponent> CapsuleComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UArrowComponent> ArrowComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComp;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
