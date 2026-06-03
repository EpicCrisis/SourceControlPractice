// This project is made by EpicCrisis
#include "C_BulletManager.h"
#include "Components/SceneComponent.h"
#include "C_Bullet.h"
#include "MyGameInstance.h"

AC_BulletManager::AC_BulletManager()
{
	PrimaryActorTick.bCanEverTick = true;

	m_SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("m_SceneComponent"));
	RootComponent = m_SceneComponent;
}

void AC_BulletManager::BeginPlay()
{
	Super::BeginPlay();

	m_GameInstance = GetGameInstance<UMyGameInstance>();
	m_GameInstance->m_BulletManager = this;
	
	if (m_BulletClass)
	{
		for (int32 i = 0; i < m_PooledBullets; ++i)
		{
			AC_Bullet* newBullet = GetWorld()->SpawnActor<AC_Bullet>
				(
					m_BulletClass,
					GetActorTransform()
					//this,
					//nullptr,
					//ESpawnActorCollisionHandlingMethod::AlwaysSpawn
				);
			//newBullet->FinishSpawning(GetActorTransform());
			m_BulletList.Add(newBullet);
		}
	}
}

void AC_BulletManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_BulletManager::CheckShootBullet(FVector shootLoc, FVector playerDirection)
{
	AC_Bullet* currentBullet = nullptr;
	for (int32 i = 0; i < m_BulletList.Num(); ++i)
	{
		if (m_BulletList[i] && !m_BulletList[i]->m_IsActive)
		{
			m_BulletList[i]->ActivateBullet(shootLoc, playerDirection);
			break;
		}
	}
}

