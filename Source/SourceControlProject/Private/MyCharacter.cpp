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
	
	m_CurrentHealth = m_MaxHealth;

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
		}
	}
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (m_IndexCounter > m_StartDelay)
	{
		//FVector currentLoc = GetActorLocation();
		//currentLoc.Y += m_MoveSpeed * DeltaTime;
		//SetActorLocation(currentLoc);

		FVector currentLoc = m_Wheelchair->GetActorLocation();
		currentLoc.Y += m_MoveSpeed * DeltaTime;
		m_Wheelchair->SetActorLocation(currentLoc);
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

void AMyCharacter::TakePlayerDamage(int32 damage)
{
	m_CurrentHealth -= damage;

	if (m_NewPlayerHud)
	{
		FText newText = FText::Format(FText::FromString(TEXT("HEALTH : {0}")), FText::AsNumber(m_CurrentHealth));
		m_NewPlayerHud->SetHealthText(newText);
	}
}

