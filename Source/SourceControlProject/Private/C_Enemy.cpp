// This project is made by EpicCrisis
#include "C_Enemy.h"
#include "Components/SceneComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/SphereComponent.h"
#include "C_Bullet.h"
#include "MyGameInstance.h"
#include "MyCharacter.h"
#include "C_Shake.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

AC_Enemy::AC_Enemy()
{
	PrimaryActorTick.bCanEverTick = true;

	m_SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("m_SceneComponent"));
	RootComponent = m_SceneComponent;
	m_EnemyBB = CreateDefaultSubobject<UBillboardComponent>(TEXT("m_EnemyBB"));
	m_EnemyBB->SetupAttachment(m_SceneComponent);
	m_KillBB = CreateDefaultSubobject<UBillboardComponent>(TEXT("m_KillBB"));
	m_KillBB->SetupAttachment(m_SceneComponent);
	m_SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("m_SphereCollider"));
	m_SphereCollider->SetupAttachment(m_SceneComponent);
	m_ShakeComponent = CreateDefaultSubobject<UC_Shake>(TEXT("m_ShakeComponent"));
}

void AC_Enemy::BeginPlay()
{
	Super::BeginPlay();

	m_SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AC_Enemy::OnSphereBeginOverlap);
	m_SphereCollider->OnComponentEndOverlap.AddDynamic(this, &AC_Enemy::OnSphereEndOverlap);

	m_CurrentHealth = m_MaxHealth;

	if (m_KillBB)
	{
		m_KillBB->SetVisibility(false);
	}
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
		HandleChase(DeltaTime);
		break;
	case E_EnemyState::Die:
		//split in half
		HandleDeath(DeltaTime);
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
			//m_ShakeDuration = m_DamageShakeDuration;
			//m_ShakeIntensity = m_DamageShakeIntensity;
			//StartDamageShake(m_EnemyBB);
			--m_CurrentHealth;
			if (m_CurrentHealth <= 0)
			{
				SetEnemyState(E_EnemyState::Die);
				//DeactivateEnemy();
			}
			else
			{
				StartDamageFlash();
				m_ShakeComponent->StartShake(m_EnemyBB, m_DamageShakeDuration, m_DamageShakeIntensity);
			}
			AC_Bullet* bullet = Cast<AC_Bullet>(OtherActor);
			if (bullet)
			{
				bullet->DeactivateBullet();
			}
		}
		//collision with player
		if (OtherActor && OtherActor->ActorHasTag(TEXT("PlayerCharacter")))
		{
			AMyCharacter* tempChar = Cast<AMyCharacter>(OtherActor);
			tempChar->TakePlayerDamage(m_AttackDamage);

			//deactivate self and explode
			ExplodeThenDisappear();
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
	m_CurrentHealth = m_MaxHealth;
	m_EnemyBB->SetWorldScale3D(FVector(1.5f));
	m_EnemyBB->MarkRenderStateDirty();
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
		FVector currentScale = m_EnemyBB->GetComponentScale();
		currentScale = FMath::VInterpTo(currentScale, FVector(1.0f), deltaTime, 10.0f);
		m_EnemyBB->SetWorldScale3D(currentScale);
		m_EnemyBB->MarkRenderStateDirty();
	}
}

void AC_Enemy::HandleChase(float deltaTime)
{
	if (!m_PlayerChar)
	{
		m_PlayerChar = GetGameInstance<UMyGameInstance>()->m_PlayerChar;
	}
	m_AttackLocation = m_PlayerChar->GetActorLocation();
	m_AttackLocation.Y = GetActorLocation().Y; //don't move forward
	FVector currentLoc = GetActorLocation();
	currentLoc = FMath::VInterpConstantTo(currentLoc, m_AttackLocation, deltaTime, 100.0f);
	SetActorLocation(currentLoc);
}

void AC_Enemy::HandleDeath(float deltaTime)
{
	if (m_KillBB && !m_KillBB->IsVisible())
	{
		m_KillBB->SetVisibility(true);
		m_KillBB->SetWorldScale3D(FVector(2.0f));

		//look at player
		FRotator currentRot = GetActorRotation();

		//m_KillBB->Sprite->

		//avoid z fighting
		FVector currentLoc = m_KillBB->GetComponentLocation();
		currentLoc.Y -= 10.0f;
		m_KillBB->SetWorldLocation(currentLoc);		
		m_KillBB->MarkRenderStateDirty();

		//m_ShakeDuration = m_CrossShakeDuration;
		//m_ShakeIntensity = m_CrossShakeIntensity;
		//StartDamageShake(m_KillBB);
		m_ShakeComponent->StartShake(m_KillBB, m_CrossShakeDuration, m_CrossShakeIntensity);
	}
	if (m_DeathCounter > m_DeathTime)
	{
		ExplodeThenDisappear();

		//spawn explosion
		//if (m_ExplodeVFX)
		//{
		//	//UNiagaraSystem::
		//
		//	//UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		//	//	GetWorld(),
		//	//	ExplosionEffect,
		//	//	GetActorLocation(),
		//	//	FRotator::ZeroRotator
		//	//);
		//
		//	//UNiagaraSystem
		//
		//	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		//		GetWorld(),
		//		m_ExplodeVFX,
		//		GetActorLocation(),
		//		FRotator::ZeroRotator
		//	);
		//}

		//m_DeathCounter = 0.0f;
		//DeactivateEnemy();
	}
	else
	{
		m_DeathCounter += deltaTime;
		FVector currentScale = m_KillBB->GetComponentScale();
		currentScale = FMath::VInterpTo(currentScale, FVector(1.0f), deltaTime, 20.0f);
		m_KillBB->SetWorldScale3D(currentScale);
		m_KillBB->MarkRenderStateDirty();		
	}
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

//void AC_Enemy::StartDamageShake(UBillboardComponent* BBComp)
//{
//	m_ShakeElapsed = 0.0f;
//	m_OriginalLoc = BBComp->GetComponentLocation();
//
//	FTimerDelegate timerDel;
//	timerDel.BindUFunction(this, FName("UpdateDamageShake"), BBComp);
//
//	GetWorld()->GetTimerManager().SetTimer(
//		ShakeTimerHandle,
//		timerDel,
//		0.01f, // tick rate (100 fps-like update)
//		true
//	);
//}

//void AC_Enemy::UpdateDamageShake(UBillboardComponent* BBComp)
//{
//	m_ShakeElapsed += 0.01f;
//
//	float alpha = m_ShakeElapsed / m_ShakeDuration;
//
//	// optional fade-out
//	float currentIntensity = m_ShakeIntensity * (1.0f - alpha);
//
//	FVector randomOffset = FVector(
//		FMath::FRandRange(-1.0f, 1.0f),
//		FMath::FRandRange(-1.0f, 1.0f),
//		FMath::FRandRange(-1.0f, 1.0f)
//	) * currentIntensity;
//
//	BBComp->SetWorldLocation(m_OriginalLoc + randomOffset);
//
//	if (m_ShakeElapsed >= m_ShakeDuration)
//	{
//		EndDamageShake(BBComp);
//	}
//}

//void AC_Enemy::EndDamageShake(UBillboardComponent* BBComp)
//{
//	GetWorld()->GetTimerManager().ClearTimer(ShakeTimerHandle);
//	BBComp->SetWorldLocation(m_OriginalLoc);
//}

void AC_Enemy::ExplodeThenDisappear()
{
	if (m_ExplodeVFX)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			m_ExplodeVFX,
			GetActorLocation(),
			FRotator::ZeroRotator
		);
	}
	m_DeathCounter = 0.0f;
	DeactivateEnemy();
}

void AC_Enemy::DeactivateEnemy()
{
	m_IsActive = false;
	SetActorLocation(FVector(0.0f, 0.0f, -10000.0f));
	m_KillBB->SetVisibility(false);
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
