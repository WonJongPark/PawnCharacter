#include "MyGameMode.h"

#include "MyPlayerController.h"
#include "ThirdPersonPawn.h"

AMyGameMode::AMyGameMode()
{
	DefaultPawnClass = AThirdPersonPawn::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
