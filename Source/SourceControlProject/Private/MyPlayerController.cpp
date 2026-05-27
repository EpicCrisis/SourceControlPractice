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
