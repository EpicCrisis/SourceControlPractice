// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

class AMyCharacter;
class UMyGameInstance;
class UCSecondHud;
class UCMainMenu;
class UCGameOver;
class AC_EnemyManager;
class AC_StreetManager;

UENUM(BlueprintType)
enum class E_CurrentGameState : uint8
{
	MainMenu		UMETA(DisplayName = "MainMenu"),
	Playing			UMETA(DisplayName = "Playing"),
	GameEnd			UMETA(DisplayName = "GameEnd")
};

UCLASS()
class SOURCECONTROLPROJECT_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	bool m_IsFirstStart = false;

	UPROPERTY()
	E_CurrentGameState m_ThisGameState = E_CurrentGameState::MainMenu;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> m_RestartLevel = nullptr;

	//check health is zero, check distance travelled
	UPROPERTY()
	AMyCharacter* m_PlayerChar = nullptr;
	UPROPERTY()
	UMyGameInstance* m_GameInstance = nullptr;
	UPROPERTY()
	AC_EnemyManager* m_EnemyManager = nullptr;
	UPROPERTY()
	AC_StreetManager* m_StreetManager = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCMainMenu> m_MainMenuClass = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCGameOver> m_GameOverClass = nullptr;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TSubclassOf<> m_UpgradeClass = nullptr;

	//remove hud and spawn menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCSecondHud* m_PlayerHud = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCMainMenu* m_MainMenu = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCGameOver* m_GameOver = nullptr;

	UFUNCTION()
	void StartGameNow(UCMainMenu* menuToClose);
	UFUNCTION()
	void QuitGameNow();
	UFUNCTION()
	void RestartMap();
};
