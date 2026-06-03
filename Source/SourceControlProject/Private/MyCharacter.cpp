// This project is made by EpicCrisis
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "C_BulletManager.h"
#include "MyGameInstance.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = false;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("The player character is spawned"));

	m_MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	m_CurrentHealth = m_MaxHealth;
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (m_IndexCounter > m_StartDelay)
	{
		FVector currentLoc = GetActorLocation();
		currentLoc.Y += m_MoveSpeed * DeltaTime;
		SetActorLocation(currentLoc);
	}
	else
	{
		m_IndexCounter += DeltaTime;
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
}

void AMyCharacter::CharacterTurn(float Value)
{
	AddControllerYawInput(Value);
}

void AMyCharacter::CharacterLookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AMyCharacter::CharacterDownLeftClick()
{
	if (m_IsDownLeftClick) return;
	m_IsDownLeftClick = true;

	if (m_BulletManager == nullptr) 
	{
		m_BulletManager = GetGameInstance<UMyGameInstance>()->m_BulletManager;
	}
	m_BulletManager->CheckShootBullet(GetActorLocation(), GetActorForwardVector());

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,                
			5.0f,              
			FColor::Green,     
			TEXT("Click Left Down") 
		);
	}
}

void AMyCharacter::CharacterUpLeftClick()
{
	if (!m_IsDownLeftClick) return;
	m_IsDownLeftClick = false;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.0f,
			FColor::Green,
			TEXT("Click Left Up")
		);
	}
}

void AMyCharacter::CharacterDownRightClick()
{
	if (m_IsDownRightClick) return;
	m_IsDownRightClick = true;
}

void AMyCharacter::CharacterUpRightClick()
{
	if (m_IsDownRightClick) return;
	m_IsDownRightClick = false;
}

