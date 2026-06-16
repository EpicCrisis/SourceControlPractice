// This project is made by EpicCrisis
#include "C_BulletManager.h"
#include "Components/SceneComponent.h"
#include "C_Bullet.h"
#include "MyGameInstance.h"
#include "CSecondHud.h"
#include "Components/TextBlock.h"
#include "MyCharacter.h"

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
		for (int32 i = 0; i < m_PooledBullet; ++i)
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
			newBullet->m_BulletManager = this;
			m_BulletList.Add(newBullet);
		}
	}

	m_GotBullet = m_PooledBullet;
}

void AC_BulletManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_DoOnce)
	{
		m_DoOnce = true;
		SetBulletText(m_GotBullet);
	}
}

void AC_BulletManager::CheckShootBullet(FVector shootLoc, FVector playerDirection)
{
	AC_Bullet* currentBullet = nullptr;
	for (int32 i = 0; i < m_BulletList.Num(); ++i)
	{
		if (m_BulletList[i] && !m_BulletList[i]->m_IsActive && !m_BulletList[i]->m_IsReloading)
		{
			m_BulletList[i]->ActivateBullet(shootLoc, playerDirection);
			--m_GotBullet;
			SetBulletText(m_GotBullet);

			break;
		}
	}
}

void AC_BulletManager::SetBulletText(int32 numberBullet)
{
	if (!m_PlayerCharacter)
	{
		m_PlayerCharacter = m_GameInstance->m_PlayerChar;
		if (!m_NewPlayerHud)
		{
			m_NewPlayerHud = m_PlayerCharacter->m_NewPlayerHud;
		}
	}
	FText newText = FText::Format(
		FText::FromString(TEXT("BULLET : {0}")),
		FText::AsNumber(numberBullet)
	);
	m_NewPlayerHud->SetBulletText(newText);
}

