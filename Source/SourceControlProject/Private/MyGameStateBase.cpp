// This project is made by EpicCrisis
#include "MyGameStateBase.h"
#include "CMainMenu.h"
#include "MyPlayerController.h"
#include "Engine/GameViewportClient.h"
#include "MyCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void AMyGameStateBase::StartGameNow(UCMainMenu* menuToClose)
{
	m_MainMenu = menuToClose;
	m_MainMenu->SetVisibility(ESlateVisibility::Collapsed);

	m_IsFirstStart = false;
	m_ThisGameState = E_CurrentGameState::Playing;

	if (AMyPlayerController* tempController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		tempController->SetGameCursor();
	}
	if (m_PlayerChar)
	{
		m_PlayerChar->ShowHud();
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

void AMyGameStateBase::RestartMap()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), m_RestartLevel);
}
