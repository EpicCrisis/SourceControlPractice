// This project is made by EpicCrisis
#include "MyPlayerController.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "EngineUtils.h"
#include "SceneView.h"

void AMyPlayerController::BeginPlay()
{
	bShowMouseCursor = false;
	SetInputMode(FInputModeUIOnly());
}

void AMyPlayerController::Tick(float DeltaTime)
{
}

void AMyPlayerController::SetMouseCursor(TSharedPtr<SWidget> InWidgetToFocus)
{
	FInputModeGameAndUI InputMode;
	InputMode.SetWidgetToFocus(InWidgetToFocus);
	SetInputMode(InputMode);
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void AMyPlayerController::SetGameCursor()
{
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = false;
	bEnableClickEvents = false;
	bEnableMouseOverEvents = false;
}
