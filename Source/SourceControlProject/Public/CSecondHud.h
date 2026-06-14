// This project is made by EpicCrisis
#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSecondHud.generated.h"

class UTextBlock;

UCLASS()
class SOURCECONTROLPROJECT_API UCSecondHud : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* m_HealthText = nullptr;

	UFUNCTION(BlueprintCallable)
	void SetHealthText(const FText& newMessage);
};
