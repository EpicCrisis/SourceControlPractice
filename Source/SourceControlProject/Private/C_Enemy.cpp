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
#include "CSecondHud.h"
#include "Components/TextBlock.h"
#include "MyGameStateBase.h"

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

	m_GameState = GetWorld()->GetGameState<AMyGameStateBase>();
	m_GameInstance = GetGameInstance<UMyGameInstance>();
}

void AC_Enemy::Tick(float DeltaTime)
{
	if (!m_IsActive)
	{
		return;
	}
	
	Super::Tick(DeltaTime);

	switch (m_GameState->m_ThisGameState)
	{
	case E_CurrentGameState::MainMenu:
		break;
	case E_CurrentGameState::Playing:

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

		break;
	case E_CurrentGameState::GameEnd:
		break;
	}
}

void AC_Enemy::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		if (!m_IsActive) return;

		if (!m_PlayerChar)
		{
			m_PlayerChar = m_GameInstance->m_PlayerChar;
		}
		if (!m_NewPlayerHud)
		{
			m_NewPlayerHud = m_PlayerChar->m_NewPlayerHud;
		}

		//if (m_EnemyState == E_EnemyState::Die) return;
		if (OtherActor && OtherActor->ActorHasTag(TEXT("PlayerBullet")))
		{
			--m_CurrentHealth;
			if (m_CurrentHealth <= 0)
			{
				SetEnemyState(E_EnemyState::Die);
				m_NewPlayerHud->m_EnemyText->SetVisibility(ESlateVisibility::Hidden);

				//get money
				m_GameInstance->m_PlayerMoney += 2;
				m_NewPlayerHud->SetMoneyText(m_GameInstance->m_PlayerMoney);
				m_GameInstance->SaveUpgrade();
			}
			else
			{
				StartDamageFlash();
				m_ShakeComponent->StartShake(m_EnemyBB, m_DamageShakeDuration, m_DamageShakeIntensity);

				FText newText = FText::Format(
					FText::FromString(TEXT("ENEMY : {0}")), 
					FText::AsNumber(m_CurrentHealth)
				);
				m_NewPlayerHud->SetEnemyText(newText);
				m_NewPlayerHud->m_EnemyText->SetVisibility(ESlateVisibility::Visible);
			}
			AC_Bullet* bullet = Cast<AC_Bullet>(OtherActor);
			if (bullet)
			{
				//bullet->DeactivateBullet();
				bullet->RemoveBullet();
			}
		}
		//collision with player
		if (OtherActor && OtherActor->ActorHasTag(TEXT("PlayerCharacter"))
			&& m_EnemyState != E_EnemyState::Die)
		{
			AMyCharacter* tempChar = Cast<AMyCharacter>(OtherActor);
			tempChar->TakePlayerDamage(m_AttackDamage);

			//deactivate self and explode
			ExplodeThenDisappear();

			m_NewPlayerHud->m_EnemyText->SetVisibility(ESlateVisibility::Hidden);
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
	if (!m_PlayerChar)
	{
		m_PlayerChar = m_GameInstance->m_PlayerChar;
	}
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
		m_PlayerChar = m_GameInstance->m_PlayerChar;
	}
	m_AttackLocation = m_PlayerChar->GetActorLocation();
	m_AttackLocation.Y = GetActorLocation().Y; //don't move forward
	FVector currentLoc = GetActorLocation();
	//currentLoc = FMath::VInterpConstantTo(currentLoc, m_AttackLocation, deltaTime, 100.0f);
	currentLoc = FMath::VInterpTo(currentLoc, m_AttackLocation, deltaTime, 0.5f);
	SetActorLocation(currentLoc);
}

void AC_Enemy::HandleDeath(float deltaTime)
{
	if (m_KillBB && !m_KillBB->IsVisible())
	{
		m_KillBB->SetVisibility(true);
		m_KillBB->SetWorldScale3D(FVector(2.0f));

		//player loc
		FVector playerLoc = m_PlayerChar->GetActorLocation();

		//avoid z fighting
		FVector currentLoc = m_KillBB->GetComponentLocation();
		
		FVector directionV = (playerLoc - currentLoc).GetSafeNormal();
		FVector distanceV = currentLoc + directionV * 10.0f;
		
		//currentLoc.Y -= 10.0f;
		m_KillBB->SetWorldLocation(distanceV);
		m_KillBB->MarkRenderStateDirty();

		m_ShakeComponent->StartShake(m_KillBB, m_CrossShakeDuration, m_CrossShakeIntensity);
	}
	if (m_DeathCounter > m_DeathTime)
	{
		ExplodeThenDisappear();
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
