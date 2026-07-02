// This project is made by EpicCrisis
#include "MyGameStateBase.h"
#include "CMainMenu.h"
#include "MyPlayerController.h"
#include "Engine/GameViewportClient.h"
#include "MyCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"
#include "CUpgradeScreen.h"

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

void AMyGameStateBase::ShowUpgradeScreen()
{
	if (m_PlayerChar)
	{
		m_PlayerChar->ShowUpgrade();
	}
}

void AMyGameStateBase::ShowMainScreen()
{
	if (m_PlayerChar)
	{
		m_PlayerChar->ShowMenu();
	}
}

void AMyGameStateBase::UpgradeBullet()
{
	//if (m_GameInstance->m_PlayerMoney >= m_GameInstance->m_BulletBaseCost)
	{
		++m_GameInstance->m_BulletUpgradeLevel;
		m_GameInstance->SaveUpgrade();

		m_UpgradeScreen->CheckPlayerMoney(m_GameInstance->m_PlayerMoney);
	}
	//else
	{

	}
}

void AMyGameStateBase::UpgradeHealth()
{
	//if (m_GameInstance->m_PlayerMoney >= m_GameInstance->m_HealthBaseCost)
	{
		++m_GameInstance->m_HealthUpgradeLevel;
		m_GameInstance->SaveUpgrade();

		m_UpgradeScreen->CheckPlayerMoney(m_GameInstance->m_PlayerMoney);
	}
	//else
	{

	}
}
