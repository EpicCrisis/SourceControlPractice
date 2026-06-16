// This project is made by EpicCrisis
#include "C_Bullet.h"
#include "Components/SceneComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/SphereComponent.h"
#include "C_BulletManager.h"

AC_Bullet::AC_Bullet()
{
	PrimaryActorTick.bCanEverTick = true;

	m_SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("m_SceneComponent"));
	RootComponent = m_SceneComponent;
	m_BulletBB = CreateDefaultSubobject<UBillboardComponent>(TEXT("m_BulletBB"));
	m_BulletBB->SetupAttachment(m_SceneComponent);
	m_SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("m_SphereCollider"));
	m_SphereCollider->SetupAttachment(m_SceneComponent);
}

void AC_Bullet::BeginPlay()
{
	Super::BeginPlay();

	m_SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AC_Bullet::OnSphereBeginOverlap);
	m_SphereCollider->OnComponentEndOverlap.AddDynamic(this, &AC_Bullet::OnSphereEndOverlap);
}

void AC_Bullet::Tick(float DeltaTime)
{
	if (!m_IsActive && !m_IsReloading) return;

	Super::Tick(DeltaTime);
	if (m_LifeTimeCounter > m_LifeTime)
	{
		//allows bullet to be used again
		DeactivateBullet();
	}
	else
	{
		m_LifeTimeCounter += DeltaTime;
	}

	FVector currentLoc = GetActorLocation();
	FVector forwardLoc = currentLoc + m_FlyingDirection * m_BulletSpeed;
	SetActorLocation(forwardLoc);
}

void AC_Bullet::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		if (!m_IsActive) return;

		if (OtherActor && OtherActor->ActorHasTag(TEXT("Obstacle")))
		{
			RemoveBullet();
		}
	}
}

void AC_Bullet::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AC_Bullet::ActivateBullet(FVector activeLoc, FVector direction)
{
	m_IsActive = true;
	m_IsReloading = false;
	m_LifeTimeCounter = 0.0f;
	SetActorLocation(activeLoc);
	m_FlyingDirection = direction;
}

void AC_Bullet::DeactivateBullet()
{
	m_IsActive = false;
	m_IsReloading = false;
	m_LifeTimeCounter = 0.0f;
	SetActorLocation(FVector(0.0f, 0.0f, -10000.0f));
	if (m_BulletManager)
	{
		++m_BulletManager->m_GotBullet;
		m_BulletManager->SetBulletText(m_BulletManager->m_GotBullet);
	}
}

void AC_Bullet::RemoveBullet()
{
	m_IsActive = false;
	m_IsReloading = true;
	SetActorLocation(FVector(0.0f, 0.0f, -10000.0f));
}

