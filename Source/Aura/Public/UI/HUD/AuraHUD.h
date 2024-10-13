// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraOverlay;

UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults | Overlay")
	TSubclassOf<UAuraOverlay> OverlayBP;
	UPROPERTY()
	TObjectPtr<UAuraOverlay> Overlay;

public:
	void InitOverlay(APlayerController* PC);
	void StartOverlay();
	void EndOverlay();
};
