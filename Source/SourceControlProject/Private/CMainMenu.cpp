// This project is made by EpicCrisis
#include "CMainMenu.h"
#include "Components/Button.h"
#include "MyGameStateBase.h"
#include "CGameOver.h"
#include "CUpgradeScreen.h"

void UCMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	StartButton->OnClicked.AddDynamic(this, &UCMainMenu::OnStartButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UCMainMenu::OnQuitButtonClicked);
	UpgradeButton->OnClicked.AddDynamic(this, &UCMainMenu::OnUpgradeButtonClicked);
	ExtraButton->OnClicked.AddDynamic(this, &UCMainMenu::OnExtraButtonClicked);
}

void UCMainMenu::OnStartButtonClicked()
{
	if (AMyGameStateBase* tempGS = GetWorld()->GetGameState<AMyGameStateBase>())
	{
		tempGS->StartGameNow(this);
	}
}

void UCMainMenu::OnQuitButtonClicked()
{
	if (AMyGameStateBase* tempGS = GetWorld()->GetGameState<AMyGameStateBase>())
	{
		tempGS->QuitGameNow();
	}
}

void UCMainMenu::OnUpgradeButtonClicked()
{
	if (AMyGameStateBase* tempGS = GetWorld()->GetGameState<AMyGameStateBase>())
	{
		tempGS->ShowUpgradeScreen();
	}
}

void UCMainMenu::OnExtraButtonClicked()
{
	if (AMyGameStateBase* tempGS = GetWorld()->GetGameState<AMyGameStateBase>())
	{
		tempGS->ShowExtraPage();
	}
}


//FReply UCMainMenu::NativeOnKeyDown(
//	const FGeometry& MyGeometry,
//	const FKeyEvent& InKeyEvent)
//{
//	if (InKeyEvent.GetKey() == EKeys::P)
//	{
//		OnTogglePause();
//		return FReply::Handled();
//	}
//
//	return Super::NativeOnKeyDown(MyGeometry, InKeyEvent);
//}
//
//void UCMainMenu::OnTogglePause()
//{
//	if (AMyGameStateBase* tempGS = GetWorld()->GetGameState<AMyGameStateBase>())
//	{
//		tempGS->StartGameNow(this);
//	}
//}
