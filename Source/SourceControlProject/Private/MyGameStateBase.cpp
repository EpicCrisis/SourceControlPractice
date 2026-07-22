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
#include "C_BulletManager.h"
#include "CExtraPage.h"

void AMyGameStateBase::StartGameNow(UCMainMenu* menuToClose)
{
	m_MainMenu = menuToClose;
	m_MainMenu->SetVisibility(ESlateVisibility::Collapsed);

	m_IsFirstStart = false;
	m_ThisGameState = E_CurrentGameState::Playing;

	m_GameInstance = GetGameInstance<UMyGameInstance>();

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
		m_GameInstance = GetGameInstance<UMyGameInstance>();
		m_PlayerChar->ShowUpgrade();
	}
}

void AMyGameStateBase::ShowMainScreen()
{
	if (m_PlayerChar)
	{
		m_PlayerChar->ShowMenu();
		m_PlayerChar->UpdateHealthStats();
		m_BulletManager->UpdatePooledBullets();
	}
}

void AMyGameStateBase::UpgradeBullet()
{
	if (m_GameInstance->m_PlayerMoney >= m_GameInstance->m_BulletBaseCost)
	{
		m_GameInstance->m_PlayerMoney -= m_GameInstance->m_BulletBaseCost;
		++m_GameInstance->m_BulletUpgradeLevel;
		m_GameInstance->SaveUpgrade();

		m_GameInstance->m_BulletBaseCost = 100 + m_GameInstance->m_BulletUpgradeLevel * 100;

		m_UpgradeScreen->UpdateTimesBullet(m_GameInstance->m_BulletUpgradeLevel);
		m_UpgradeScreen->UpdateMaxBulletCost(m_GameInstance->m_BulletBaseCost);
		m_UpgradeScreen->CheckPlayerMoney(m_GameInstance->m_PlayerMoney);
	}
	else
	{

	}
}

void AMyGameStateBase::UpgradeHealth()
{
	if (m_GameInstance->m_PlayerMoney >= m_GameInstance->m_HealthBaseCost)
	{
		m_GameInstance->m_PlayerMoney -= m_GameInstance->m_HealthBaseCost;
		++m_GameInstance->m_HealthUpgradeLevel;
		m_GameInstance->SaveUpgrade();

		m_GameInstance->m_HealthBaseCost = 100 + m_GameInstance->m_HealthUpgradeLevel * 100;

		m_UpgradeScreen->UpdateTimesHealth(m_GameInstance->m_HealthUpgradeLevel);
		m_UpgradeScreen->UpdateMaxHealthCost(m_GameInstance->m_HealthBaseCost);
		m_UpgradeScreen->CheckPlayerMoney(m_GameInstance->m_PlayerMoney);
	}
	else
	{

	}
}

void AMyGameStateBase::AddMoreMoney(int32 amount)
{
	m_GameInstance->m_PlayerMoney += amount;
	m_GameInstance->SaveUpgrade();
	m_ExtraPage->CheckPlayerMoney(m_GameInstance->m_PlayerMoney);
}

void AMyGameStateBase::ShowExtraPage()
{
	if (m_PlayerChar)
	{
		m_GameInstance = GetGameInstance<UMyGameInstance>();
		m_PlayerChar->ShowExtraPage();
	}
}
