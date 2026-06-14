// This project is made by EpicCrisis
#include "CSecondHud.h"
#include "Components/TextBlock.h"

void UCSecondHud::SetHealthText(const FText& newMessage)
{
	m_HealthText->SetText(newMessage);
}


