// This project is made by EpicCrisis
#include "C_EnemyManager.h"
#include "C_Enemy.h"

AC_EnemyManager::AC_EnemyManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AC_EnemyManager::SpawnEnemyAt(FVector spawnLoc)
{
	FTransform spawnT = GetActorTransform();
	spawnT.SetLocation(spawnLoc);
	m_CurrentEnemy = GetWorld()->SpawnActorDeferred<AC_Enemy>
	(
		m_EnemyClass, 
		spawnT,
		this, 
		nullptr, 
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);
}

void AC_EnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_EnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

