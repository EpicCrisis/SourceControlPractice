// This project is made by EpicCrisis
#include "CUpgradeScreen.h"
#include "MyGameStateBase.h"
#include "Components/Button.h"
#include "MyGameInstance.h"
#include "Components/TextBlock.h"

void UCUpgradeScreen::NativeConstruct()
{
	ReturnButton->OnClicked.AddDynamic(this, &UCUpgradeScreen::OnReturnButtonClicked);
}

void UCUpgradeScreen::CheckPlayerMoney(int32 playerMoney)
{
	//m_GameInstance = GetGameInstance<UMyGameInstance>();

	FText newText = FText::Format(FText::FromString(TEXT("MONEY : {0}")), FText::AsNumber(playerMoney));
	PlayerMoneyText->SetText(newText);
}

void UCUpgradeScreen::OnReturnButtonClicked()
{
	if (AMyGameStateBase* tempGS = GetWorld()->GetGameState<AMyGameStateBase>())
	{
		tempGS->ShowMainScreen();
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
