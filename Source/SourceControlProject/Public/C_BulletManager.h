// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_BulletManager.generated.h"

class AC_Bullet;
class UMyGameInstance;

UCLASS()
class SOURCECONTROLPROJECT_API AC_BulletManager : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* m_SceneComponent = nullptr;
	UPROPERTY()
	UMyGameInstance* m_GameInstance = nullptr;


	int32 m_PooledBullets = 10;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AC_Bullet> m_BulletClass;
	UPROPERTY(VisibleAnywhere)
	TArray<AC_Bullet*> m_BulletList;

	AC_BulletManager();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void CheckShootBullet(FVector shootLoc, FVector playerDirection);
};
