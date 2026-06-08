// This project is made by EpicCrisis
#include "C_EnemyManager.h"
#include "C_Enemy.h"
#include "MyGameInstance.h"
#include "MyCharacter.h"

AC_EnemyManager::AC_EnemyManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AC_EnemyManager::SpawnEnemyAt(FVector spawnLoc)
{
	for (int32 i = 0; i < m_EnemyList.Num(); ++i)
	{
		if (m_EnemyList[i] && m_EnemyList.IsValidIndex(i))
		{
			if (!m_EnemyList[i]->m_IsActive)
			{
				m_EnemyList[i]->SpawnThisEnemy(spawnLoc);
				break;
			}
		}
	}
}

void AC_EnemyManager::PoolEnemyList()
{
	for (int32 i = 0; i < m_PooledAmount; ++i)
	{
		FTransform spawnT = GetActorTransform();
		spawnT.SetLocation(FVector(0.0f, 0.0f, -10000.0f));
		m_CurrentEnemy = GetWorld()->SpawnActorDeferred<AC_Enemy>
			(
				m_EnemyClass,
				spawnT,
				this,
				nullptr,
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);
		m_CurrentEnemy->FinishSpawning(spawnT);
		m_EnemyList.Add(m_CurrentEnemy);
		m_CurrentEnemy = nullptr;
	}
}

void AC_EnemyManager::BeginPlay()
{
	Super::BeginPlay();

	m_GameInstance = GetGameInstance<UMyGameInstance>();
	PoolEnemyList();
}

void AC_EnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_CurrentPlayer)
	{
		m_CurrentPlayer = m_GameInstance->m_PlayerChar;
	}
	if (m_SpawnCounter > m_SpawnInterval)
	{
		m_SpawnCounter = 0.0f;
		FVector nextSpawnLoc = m_CurrentPlayer->GetActorLocation();
		nextSpawnLoc.Y += m_SpawnDistance;

		//randomize in the circle
		float angle = FMath::FRandRange(0.0f, 2.0f * PI);
		float distance = m_SpawnRadius * FMath::Sqrt(FMath::FRand());

		nextSpawnLoc.X += FMath::Cos(angle) * distance;
		nextSpawnLoc.Z += m_HeightOffset + FMath::Sin(angle) * distance; //make it lift up offset

		SpawnEnemyAt(nextSpawnLoc);
	}
	else
	{
		m_SpawnCounter += DeltaTime;
	}
}

