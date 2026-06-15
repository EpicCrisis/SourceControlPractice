// This project is made by EpicCrisis
#include "CSecondHud.h"
#include "Components/TextBlock.h"

void UCSecondHud::SetHealthText(const FText& newMessage)
{
	m_HealthText->SetText(newMessage);
}

void UCSecondHud::SetDistanceText(const FText& newMessage)
{
	m_DistanceText->SetText(newMessage);
}

void UCSecondHud::SetBulletText(const FText& newMessage)
{
	m_BulletText->SetText(newMessage);
}

void UCSecondHud::SetEnemyText(const FText& newMessage)
{
	m_EnemyText->SetText(newMessage);
}


