// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class APlayerController;
class UAuraOverlay;

UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	TObjectPtr<UAuraOverlay> OverlayWidget;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraOverlay> OverlayWidgetClass;

	void CreateOverlayWidget(APlayerController* PC);
};
