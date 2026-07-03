// This project is made by EpicCrisis
#include "CUpgradeScreen.h"
#include "MyGameStateBase.h"
#include "Components/Button.h"
#include "MyGameInstance.h"
#include "Components/TextBlock.h"

void UCUpgradeScreen::NativeConstruct()
{
	ReturnButton->OnClicked.AddDynamic(this, &UCUpgradeScreen::OnReturnButtonClicked);
	MaxBulletUpgradeButton->OnClicked.AddDynamic(this, &UCUpgradeScreen::OnMaxBulletUpgradeClicked);
	MaxHealthUpgradeButton->OnClicked.AddDynamic(this, &UCUpgradeScreen::OnMaxHealthUpgradeClicked);
}

void UCUpgradeScreen::CheckPlayerMoney(int32 playerMoney)
{
	//m_GameInstance = GetGameInstance<UMyGameInstance>();

	FText newText = FText::Format(FText::FromString(TEXT("MONEY : {0}")), FText::AsNumber(playerMoney));
	PlayerMoneyText->SetText(newText);
}

void UCUpgradeScreen::OnReturnButtonClicked()
{
	//if (AMyGameStateBase* tempGS = GetWorld()->GetGameState<AMyGameStateBase>())
	//{
	//	tempGS->ShowMainScreen();
	//}

	//respawn everything
	if (AMyGameStateBase* tempGS = GetWorld()->GetGameState<AMyGameStateBase>())
	{
		tempGS->RestartMap();
	}
}

void UCUpgradeScreen::OnMaxBulletUpgradeClicked()
{
	if (AMyGameStateBase* tempGS = GetWorld()->GetGameState<AMyGameStateBase>())
	{
		tempGS->UpgradeBullet();
	}
}

void UCUpgradeScreen::OnMaxHealthUpgradeClicked()
{
	if (AMyGameStateBase* tempGS = GetWorld()->GetGameState<AMyGameStateBase>())
	{
		tempGS->UpgradeHealth();
	}
}

void UCUpgradeScreen::UpdateTimesBullet(int32 number)
{
	FText newText = FText::Format(FText::FromString(TEXT("x{0}")), FText::AsNumber(number));
	TimesBulletText->SetText(newText);
}

void UCUpgradeScreen::UpdateTimesHealth(int32 number)
{
	FText newText = FText::Format(FText::FromString(TEXT("x{0}")), FText::AsNumber(number));
	TimesHealthText->SetText(newText);
}
