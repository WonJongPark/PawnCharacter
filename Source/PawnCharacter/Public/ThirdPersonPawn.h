#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ThirdPersonPawn.generated.h"

UCLASS()
class PAWNCHARACTER_API AThirdPersonPawn : public APawn
{
	GENERATED_BODY()

public:
	AThirdPersonPawn();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
