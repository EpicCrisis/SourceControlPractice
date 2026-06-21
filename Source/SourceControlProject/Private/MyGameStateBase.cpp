// This project is made by EpicCrisis
#include "MyGameStateBase.h"
#include "CMainMenu.h"
#include "MyPlayerController.h"
#include "Engine/GameViewportClient.h"
#include "MyCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

void AMyGameStateBase::StartGameNow(UCMainMenu* menuToClose)
{
	m_MainMenu = menuToClose;
	m_MainMenu->RemoveFromParent();

	m_ThisGameState = E_CurrentGameState::Playing;

	if (AMyPlayerController* tempController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		//tempController->SetShowMouseCursor(true);
		tempController->SetGameCursor();
		m_PlayerChar->EnableInput(tempController);

		if (UGameViewportClient* Viewport = GetWorld()->GetGameViewport())
		{
			Viewport->SetMouseCaptureMode(EMouseCaptureMode::CapturePermanently);
		}
	}
}

void AMyGameStateBase::QuitGameNow()
{
	if (AMyPlayerController* tempController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		UKismetSystemLibrary::QuitGame(
			GetWorld(),
			tempController,
			EQuitPreference::Quit,
			false
		);
	}
}