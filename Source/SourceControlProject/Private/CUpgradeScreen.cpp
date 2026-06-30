// This project is made by EpicCrisis
#include "CUpgradeScreen.h"
#include "MyGameStateBase.h"
#include "Components/Button.h"

void UCUpgradeScreen::NativeConstruct()
{
	ReturnButton->OnClicked.AddDynamic(this, &UCUpgradeScreen::OnReturnButtonClicked);
}

void UCUpgradeScreen::CheckPlayerMoney(int32 playerMoney)
{
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
}

void UCUpgradeScreen::OnMaxHealthUpgradeClicked()
{
}
