// This project is made by EpicCrisis
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "C_BulletManager.h"
#include "MyGameInstance.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "C_Wheelchair.h"
#include "C_FirstHud.h"
#include "CSecondHud.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "MyGameStateBase.h"
#include "CMainMenu.h"
#include "MyPlayerController.h"
#include "CGameOver.h"
#include "CUpgradeScreen.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = false;

	//m_SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("m_SceneComponent"));
	//RootComponent = m_SceneComponent;

	//m_WheelchairSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_WheelchairSM"));
	//m_WheelchairSM->SetupAttachment(RootComponent);
	//m_WheelchairSM->SetCollisionProfileName(FName("NoCollision"));
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("The player character is spawned"));

	m_MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	m_MyGameInstance->m_PlayerChar = this;
	
	m_GameState = GetWorld()->GetGameState<AMyGameStateBase>();
	if (m_GameState)
	{
		m_GameState->m_PlayerChar = this;
		m_GameState->m_IsFirstStart = true;
	}

	//setup stats
	m_MaxHealth = 1 + m_MyGameInstance->m_HealthUpgradeLevel;
	m_CurrentHealth = m_MaxHealth;

	switch (m_GameState->m_ThisGameState)
	{
	case E_CurrentGameState::MainMenu:
	{
		if (m_GameState->m_MainMenuClass)
		{
			m_NewMainMenu = CreateWidget<UCMainMenu>(
				GetWorld(),
				m_GameState->m_MainMenuClass
			);
			if (m_NewMainMenu)
			{
				m_NewMainMenu->AddToViewport();
			}
		}
		if (m_GameState->m_GameOverClass)
		{
			m_NewGameEnd = CreateWidget<UCGameOver>(
				GetWorld(),
				m_GameState->m_GameOverClass
			);
			if (m_NewGameEnd)
			{
				m_NewGameEnd->AddToViewport();
				m_NewGameEnd->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
		if (m_GameState->m_UpgradeClass)
		{
			m_NewUpgrade = CreateWidget<UCUpgradeScreen>(
				GetWorld(),
				m_GameState->m_UpgradeClass
			);
			if (m_NewUpgrade)
			{
				m_NewUpgrade->AddToViewport();
				m_NewUpgrade->SetVisibility(ESlateVisibility::Collapsed);
				m_GameState->m_UpgradeScreen = m_NewUpgrade;
			}
		}
		if (m_WheelchairClass)
		{
			FTransform tempT = FTransform();
			tempT.SetLocation(GetActorLocation());
			m_Wheelchair = GetWorld()->SpawnActor<AC_Wheelchair>(m_WheelchairClass, tempT);
			this->AttachToActor(m_Wheelchair, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

			FVector thisLoc = GetActorLocation();
			thisLoc.Z += 50.0f;
			SetActorLocation(thisLoc);
		}
		if (m_SecondHudClass)
		{
			m_NewPlayerHud = CreateWidget<UCSecondHud>(
				GetWorld(),
				m_SecondHudClass
			);
			if (m_NewPlayerHud)
			{
				m_NewPlayerHud->AddToViewport();
				m_NewPlayerHud->m_EnemyText->SetVisibility(ESlateVisibility::Hidden);
				m_NewPlayerHud->SetVisibility(ESlateVisibility::Collapsed);
				m_NewPlayerHud->SetHealthText(m_CurrentHealth);
				m_NewPlayerHud->SetMoneyText(m_MyGameInstance->m_PlayerMoney);
			}
		}
		break;
	}
	case E_CurrentGameState::Playing:
	{
		break;
	}
	case E_CurrentGameState::GameEnd:
	{
		break;
	}
	}	
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	switch (m_GameState->m_ThisGameState)
	{
	case E_CurrentGameState::MainMenu:
	{
		if (!m_ActivateCursor)
		{
			if (AMyPlayerController* tempController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController()))
			{
				if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
				{
					GEngine->AddOnScreenDebugMessage(
						-1,
						5.f,
						FColor::Green,
						TEXT("PlayerController Found")
					);
				}
				m_PlayerController = tempController;
				m_PlayerController->SetMouseCursor(m_NewMainMenu->TakeWidget());
				m_ActivateCursor = true;
			}
		}
		break;
	}
	case E_CurrentGameState::Playing:
	{
		if (m_IndexCounter > m_StartDelay)
		{
			//FVector currentLoc = GetActorLocation();
			//currentLoc.Y += m_MoveSpeed * DeltaTime;
			//SetActorLocation(currentLoc);

			m_CurrentAcceleration += m_AccelerationRate * DeltaTime;
			if (m_CurrentAcceleration >= 100.0f)
			{
				m_CurrentAcceleration = 100.0f;
			}
			else if (m_CurrentAcceleration <= -100.0f)
			{
				m_CurrentAcceleration = -100.0f;
			}

			m_CurrentVelocity += m_CurrentAcceleration * DeltaTime;
			if (m_CurrentVelocity >= 100.0f)
			{
				m_CurrentVelocity = 100.0f;
			}
			else if (m_CurrentVelocity <= 0.0f)
			{
				m_CurrentVelocity = 0.0f;
			}
			m_MoveSpeed = m_CurrentVelocity;

			FVector currentLoc = m_Wheelchair->GetActorLocation();
			currentLoc.Y += m_MoveSpeed * DeltaTime;
			m_Wheelchair->SetActorLocation(currentLoc);

			m_DistanceTravelled += (m_MoveSpeed * DeltaTime) / 100.0f;
			if (m_NewPlayerHud)
			{
				m_NewPlayerHud->SetDistanceText(m_DistanceTravelled);
			}
			CheckDistance(m_DistanceTravelled);
		}
		else
		{
			m_IndexCounter += DeltaTime;
		}
		break;
	}
	case E_CurrentGameState::GameEnd:
	{
		break;
	}
	}
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::CharacterTurn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::CharacterLookUp);	
	PlayerInputComponent->BindAction("LeftClick", EInputEvent::IE_Pressed, this, &AMyCharacter::CharacterDownLeftClick);
	PlayerInputComponent->BindAction("LeftClick", EInputEvent::IE_Released, this, &AMyCharacter::CharacterUpLeftClick);
	PlayerInputComponent->BindAction("RightClick", EInputEvent::IE_Pressed, this, &AMyCharacter::CharacterDownRightClick);
	PlayerInputComponent->BindAction("RightClick", EInputEvent::IE_Released, this, &AMyCharacter::CharacterUpRightClick);
	PlayerInputComponent->BindAction("PKey", EInputEvent::IE_Pressed, this, &AMyCharacter::DownPause);
	PlayerInputComponent->BindAction("PKey", EInputEvent::IE_Released, this, &AMyCharacter::UpPause);
}

void AMyCharacter::UpdateHealthStats()
{
	//setup stats
	m_MaxHealth = 1 + m_MyGameInstance->m_HealthUpgradeLevel;
	m_CurrentHealth = m_MaxHealth;

	if (m_NewPlayerHud)
	{
		m_NewPlayerHud->SetHealthText(m_CurrentHealth);
		m_NewPlayerHud->SetMoneyText(m_MyGameInstance->m_PlayerMoney);
	}
}

void AMyCharacter::CharacterTurn(float Value)
{
	if (m_GameState->m_ThisGameState != E_CurrentGameState::Playing) return;
	AddControllerYawInput(Value);
}

void AMyCharacter::CharacterLookUp(float Value)
{
	if (m_GameState->m_ThisGameState != E_CurrentGameState::Playing) return;
	AddControllerPitchInput(Value);
}

void AMyCharacter::CharacterDownLeftClick()
{
	if (m_GameState->m_ThisGameState != E_CurrentGameState::Playing) return;
	if (m_IsDownLeftClick) return;
	m_IsDownLeftClick = true;

	if (m_BulletManager == nullptr) 
	{
		m_BulletManager = GetGameInstance<UMyGameInstance>()->m_BulletManager;
	}
	FVector playerLoc = GetActorLocation();
	playerLoc.Z += 20.0f;
	m_BulletManager->CheckShootBullet(playerLoc, GetActorForwardVector());

	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(
	//		-1,                
	//		5.0f,              
	//		FColor::Green,     
	//		TEXT("Click Left Down") 
	//	);
	//}
}

void AMyCharacter::CharacterUpLeftClick()
{
	if (m_GameState->m_ThisGameState != E_CurrentGameState::Playing) return;
	if (!m_IsDownLeftClick) return;
	m_IsDownLeftClick = false;
}

void AMyCharacter::CharacterDownRightClick()
{
	if (m_GameState->m_ThisGameState != E_CurrentGameState::Playing) return;
	if (m_IsDownRightClick) return;
	m_IsDownRightClick = true;
}

void AMyCharacter::CharacterUpRightClick()
{
	if (m_GameState->m_ThisGameState != E_CurrentGameState::Playing) return;
	if (m_IsDownRightClick) return;
	m_IsDownRightClick = false;
}

void AMyCharacter::DownPause()
{
	if (m_GameState->m_IsFirstStart) return;
	if (m_IsDownPKey) return;
	m_IsDownPKey = true;

	switch (m_GameState->m_ThisGameState)
	{
	case E_CurrentGameState::MainMenu: //return to play
		m_GameState->m_ThisGameState = E_CurrentGameState::Playing;
				
		m_NewMainMenu->SetVisibility(ESlateVisibility::Collapsed);
		m_NewPlayerHud->SetVisibility(ESlateVisibility::Visible);
		m_NewPlayerHud->m_EnemyText->SetVisibility(ESlateVisibility::Hidden);
		
		m_PlayerController->SetGameCursor();
		break;

	case E_CurrentGameState::Playing: //open main menu
		m_GameState->m_ThisGameState = E_CurrentGameState::MainMenu;

		m_NewPlayerHud->SetVisibility(ESlateVisibility::Collapsed);
		m_NewMainMenu->SetVisibility(ESlateVisibility::Visible);

		//cannot upgrade during gameplay
		m_NewMainMenu->UpgradeButton->SetVisibility(ESlateVisibility::Collapsed);

		m_PlayerController->SetMouseCursor(m_NewMainMenu->TakeWidget());
		//DisableInput(m_PlayerController);
		break;

	}
}

void AMyCharacter::UpPause()
{
	if (m_GameState->m_IsFirstStart) return;
	if (!m_IsDownPKey) return;
	m_IsDownPKey = false;
}

void AMyCharacter::TakePlayerDamage(int32 damage)
{
	m_CurrentHealth -= damage;

	m_CurrentAcceleration *= 0.5f;
	m_CurrentVelocity *= 0.5f;

	if (m_NewPlayerHud)
	{
		m_NewPlayerHud->SetHealthText(m_CurrentHealth);
	}
	if (m_CurrentHealth <= 0)
	{
		m_GameState->m_ThisGameState = E_CurrentGameState::GameEnd;

		m_NewPlayerHud->SetVisibility(ESlateVisibility::Collapsed);
		m_NewGameEnd->SetVisibility(ESlateVisibility::Visible);

		m_NewGameEnd->SetGameOverMessage(false);

		m_PlayerController->SetMouseCursor(m_NewGameEnd->TakeWidget());
	}
}

void AMyCharacter::ShowHud()
{
	m_NewMainMenu->SetVisibility(ESlateVisibility::Collapsed);
	m_NewPlayerHud->SetVisibility(ESlateVisibility::Visible);
	m_NewPlayerHud->m_EnemyText->SetVisibility(ESlateVisibility::Hidden);
}

void AMyCharacter::CheckDistance(float distance)
{
	if (distance >= m_VictoryDistance)
	{
		m_GameState->m_ThisGameState = E_CurrentGameState::GameEnd;

		m_NewPlayerHud->SetVisibility(ESlateVisibility::Collapsed);
		m_NewGameEnd->SetVisibility(ESlateVisibility::Visible);

		m_NewGameEnd->SetGameOverMessage(true);

		m_PlayerController->SetMouseCursor(m_NewGameEnd->TakeWidget());
	}
}

void AMyCharacter::ShowUpgrade()
{
	m_NewMainMenu->SetVisibility(ESlateVisibility::Collapsed);
	m_NewUpgrade->SetVisibility(ESlateVisibility::Visible);

	m_NewUpgrade->CheckPlayerMoney(m_MyGameInstance->m_PlayerMoney);
	m_NewUpgrade->UpdateTimesBullet(m_MyGameInstance->m_BulletUpgradeLevel);
	m_NewUpgrade->UpdateTimesHealth(m_MyGameInstance->m_HealthUpgradeLevel);

	m_NewUpgrade->UpdateMaxBulletCost(m_MyGameInstance->m_BulletBaseCost);
	m_NewUpgrade->UpdateMaxHealthCost(m_MyGameInstance->m_HealthBaseCost);
}

void AMyCharacter::ShowMenu()
{
	m_NewUpgrade->SetVisibility(ESlateVisibility::Collapsed);
	m_NewMainMenu->SetVisibility(ESlateVisibility::Visible);
}
