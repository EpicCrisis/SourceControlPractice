// This project is made by EpicCrisis
#include "CGameOver.h"
#include "Components/TextBlock.h"

void UCGameOver::SetGameOverMessage(const FText& newMessage)
{
	WinLoseText->SetText(newMessage);
}
