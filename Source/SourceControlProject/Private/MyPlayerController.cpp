// This project is made by EpicCrisis
#include "MyPlayerController.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "EngineUtils.h"
#include "SceneView.h"

void AMyPlayerController::BeginPlay()
{
	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());
}

void AMyPlayerController::Tick(float DeltaTime)
{
}

void AMyPlayerController::SetMouseCursor()
{
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void AMyPlayerController::SetGameCursor()
{
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	InputMode.SetHideCursorDuringCapture(true);
	SetInputMode(InputMode);
	bShowMouseCursor = false;
	bEnableClickEvents = false;
	bEnableMouseOverEvents = false;
}
