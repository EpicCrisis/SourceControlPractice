// This project is made by EpicCrisis
#include "C_Enemy.h"
#include "Components/SceneComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/SphereComponent.h"

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
	
}

void AC_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Enemy::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AC_Enemy::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AC_Enemy::ActivateEnemy(FVector activeLoc)
{

}

void AC_Enemy::DeactivateEnemy()
{

}
