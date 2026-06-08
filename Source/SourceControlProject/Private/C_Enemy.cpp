// This project is made by EpicCrisis
#include "C_Enemy.h"
#include "Components/SceneComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/SphereComponent.h"
#include "C_Bullet.h"
#include "MyGameInstance.h"

AC_Enemy::AC_Enemy()
{
	PrimaryActorTick.bCanEverTick = true;

	m_SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("m_SceneComponent"));
	RootComponent = m_SceneComponent;
	m_EnemyBB = CreateDefaultSubobject<UBillboardComponent>(TEXT("m_EnemyBB"));
	m_EnemyBB->SetupAttachment(m_SceneComponent);
	m_SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("m_SphereCollider"));
	m_SphereCollider->SetupAttachment(m_SceneComponent);
}

void AC_Enemy::BeginPlay()
{
	Super::BeginPlay();

	m_SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AC_Enemy::OnSphereBeginOverlap);
	m_SphereCollider->OnComponentEndOverlap.AddDynamic(this, &AC_Enemy::OnSphereEndOverlap);

	m_CurrentHealth = m_MaxHealth;
}

void AC_Enemy::Tick(float DeltaTime)
{
	if (!m_IsActive)
	{
		return;
	}
	
	Super::Tick(DeltaTime);

	switch (m_EnemyState)
	{
	case E_EnemyState::Spawn:
		HandleSpawn(DeltaTime);
		break;
	case E_EnemyState::Chase:		
		//should slowly move until it reaches center of player
		//deal collide damage to player
		HandleChase();
		break;
	case E_EnemyState::Die:
		//split in half
		HandleDeath();
		break;
	}
}

void AC_Enemy::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		if (!m_IsActive) return;
		if (OtherActor && OtherActor->ActorHasTag(TEXT("PlayerBullet")))
		{
			--m_CurrentHealth;
			StartDamageFlash();
			if (m_CurrentHealth <= 0)
			{
				DeactivateEnemy();
			}
			AC_Bullet* bullet = Cast<AC_Bullet>(OtherActor);
			if (bullet)
			{
				bullet->DeactivateBullet();
			}
		}
	}

}

void AC_Enemy::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AC_Enemy::SpawnThisEnemy(FVector spawnLoc)
{
	//Expand, then shrink a bit
	m_IsActive = true;
	m_CurrentScale = m_InitialScale;
	m_CurrentHealth = m_MaxHealth;
	SetActorScale3D(FVector(m_InitialScale));
	SetEnemyState(E_EnemyState::Spawn);
	SetActorLocation(spawnLoc);
}

void AC_Enemy::HandleSpawn(float deltaTime)
{
	//pop in and do nothing for the first 1 second
	if (m_SpawnCounter > m_SpawnIdleTime)
	{
		m_SpawnCounter = 0.0f;
		SetEnemyState(E_EnemyState::Chase);
	}
	else
	{
		m_SpawnCounter += deltaTime;
		if (!FMath::IsNearlyEqual(m_CurrentScale, m_TargetScale, 0.1f))
		{
			m_CurrentScale = FMath::FInterpConstantTo(m_CurrentScale, m_TargetScale, deltaTime, 1.0f);
			SetActorScale3D(FVector(m_CurrentScale));
		}
	}
}

void AC_Enemy::HandleChase()
{
	if (!m_PlayerChar)
	{
		m_PlayerChar = GetGameInstance<UMyGameInstance>()->m_PlayerChar;
	}
}

void AC_Enemy::HandleDeath()
{
}

void AC_Enemy::StartDamageFlash()
{
	GetWorldTimerManager().ClearTimer(DamageFlashTimer);
	m_EnemyBB->SetSprite(m_DamageFlash);

	GetWorldTimerManager().SetTimer(
		DamageFlashTimer,
		this,
		&AC_Enemy::EndDamageFlash,
		0.1f,
		false);
}

void AC_Enemy::EndDamageFlash()
{
	GetWorldTimerManager().ClearTimer(DamageFlashTimer);
	m_EnemyBB->SetSprite(m_Normal);
}

void AC_Enemy::DeactivateEnemy()
{
	m_IsActive = false;
	SetActorLocation(FVector(0.0f, 0.0f, -10000.0f));
}

void AC_Enemy::SetEnemyState(E_EnemyState state)
{
	m_EnemyState = state;
	switch (state)
	{
	case E_EnemyState::Spawn:
		break;
	case E_EnemyState::Chase:
		break;
	case E_EnemyState::Die:
		break;
	}
}
