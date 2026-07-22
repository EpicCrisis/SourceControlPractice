// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "MyCharacter.generated.h"

class UMyGameInstance;
class AC_BulletManager;
class UStaticMeshComponent;
class USceneComponent;
class AC_Wheelchair;
class UC_FirstHud;
class UCSecondHud;
class AMyGameStateBase;
class UCMainMenu;
class UCGameOver;
class AMyPlayerController;
class UCUpgradeScreen;
class UCExtraPage;

UCLASS()
class SOURCECONTROLPROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//UStaticMeshComponent* m_WheelchairSM = nullptr;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//USceneComponent* m_SceneComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AC_Wheelchair> m_WheelchairClass = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AC_Wheelchair* m_Wheelchair = nullptr;
	
	UPROPERTY()
	AMyGameStateBase* m_GameState = nullptr;
	
	//UPROPERTY()
	//UC_FirstHUD* m_PlayerHUD = nullptr;

	UPROPERTY()
	bool m_ActivateCursor = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCMainMenu* m_NewMainMenu = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCSecondHud* m_NewPlayerHud = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCGameOver* m_NewGameEnd = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCUpgradeScreen* m_NewUpgrade = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCExtraPage* m_ExtraPage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AMyPlayerController* m_PlayerController = nullptr;

	UPROPERTY()
	float m_DistanceTravelled = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_VictoryDistance = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCSecondHud> m_SecondHudClass = nullptr;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//UUserWidget* m_PlayerHud = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_AccelerationRate = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_CurrentAcceleration = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_CurrentVelocity = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_StartDelay = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_MoveSpeed = 100.0f;
	UPROPERTY()
	float m_IndexCounter = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 m_MaxHealth = 3;
	UPROPERTY()
	int32 m_CurrentHealth = 3;
	UPROPERTY()
	bool m_IsDownLeftClick = false;
	//UPROPERTY()
	//bool m_IsUpLeftClick = false;
	UPROPERTY()
	bool m_IsDownRightClick = false;
	//UPROPERTY()
	//bool m_IsUpRightClick = false;
	UPROPERTY()
	bool m_IsDownPKey = false;

	UPROPERTY()
	UMyGameInstance* m_MyGameInstance = nullptr;
	UPROPERTY()
	AC_BulletManager* m_BulletManager = nullptr;

	AMyCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UpdateHealthStats();

	void CharacterTurn(float Value);
	void CharacterLookUp(float Value);
	void CharacterDownLeftClick();
	void CharacterUpLeftClick();
	void CharacterDownRightClick();
	void CharacterUpRightClick();
	void DownPause();
	void UpPause();

	UFUNCTION()
	void TakePlayerDamage(int32 damage);
	UFUNCTION()
	void ShowHud();
	UFUNCTION()
	void CheckDistance(float distance);
	UFUNCTION()
	void ShowUpgrade();
	UFUNCTION()
	void ShowMenu();
	UFUNCTION()
	void ShowExtraPage();
};
