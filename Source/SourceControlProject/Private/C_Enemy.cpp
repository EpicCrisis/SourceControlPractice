// This project is made by EpicCrisis
#include "C_Enemy.h"
#include "Components/SceneComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/SphereComponent.h"
#include "C_Bullet.h"

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
	Super::Tick(DeltaTime);

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
		}
	}

}

void AC_Enemy::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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
		0.2f,
		false);
}

void AC_Enemy::EndDamageFlash()
{
	GetWorldTimerManager().ClearTimer(DamageFlashTimer);
	m_EnemyBB->SetSprite(m_Normal);
}

void AC_Enemy::ActivateEnemy(FVector activeLoc)
{
	m_IsActive = true;
	m_CurrentHealth = m_MaxHealth;
}

void AC_Enemy::DeactivateEnemy()
{
	m_IsActive = false;
	SetActorLocation(FVector(0.0f, 0.0f, -10000.0f));
}
