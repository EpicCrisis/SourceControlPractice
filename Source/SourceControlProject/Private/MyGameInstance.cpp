// This project is made by EpicCrisis
#include "MyGameInstance.h"
#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"

void UMyGameInstance::Init()
{
	Super::Init();

	LoadOrCreateSave();

	UE_LOG(LogTemp, Warning, TEXT("GameInstance Initialized"));
}

void UMyGameInstance::Shutdown()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Shutdown"));

	Super::Shutdown();
}

void UMyGameInstance::SaveUpgrade()
{
	SaveSlotName = FString("SaveGameZero");
	UserIndex = 0;

	UMySaveGame* SaveGame = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));

	SaveGame->m_PlayerMoney = m_PlayerMoney;
	SaveGame->m_BulletUpgrade = m_BulletUpgradeLevel;
	SaveGame->m_HealthUpgrade = m_HealthUpgradeLevel;

	UGameplayStatics::SaveGameToSlot(SaveGame, SaveSlotName, UserIndex);
}

void UMyGameInstance::LoadUpgrade()
{
	SaveSlotName = FString("SaveGameZero");
	UserIndex = 0;

	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
	{
		UMySaveGame* SaveGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));

		if (SaveGame)
		{
			m_PlayerMoney = SaveGame->m_PlayerMoney;
			m_BulletUpgradeLevel = SaveGame->m_BulletUpgrade;
			m_HealthUpgradeLevel = SaveGame->m_HealthUpgrade;

			m_BulletBaseCost = 100 + m_BulletUpgradeLevel * 100;
			m_HealthBaseCost = 100 + m_HealthUpgradeLevel * 100;
		}
	}
}

void UMyGameInstance::LoadOrCreateSave()
{
	SaveSlotName = FString("SaveGameZero");
	UserIndex = 0;

	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
	{
		LoadUpgrade();
	}
	else
	{
		m_PlayerMoney = 100;
		m_BulletUpgradeLevel = 0;
		m_HealthUpgradeLevel = 0;

		m_BulletBaseCost = 100 + m_BulletUpgradeLevel * 100;
		m_HealthBaseCost = 100 + m_HealthUpgradeLevel * 100;
		
		SaveUpgrade();
	}
}
