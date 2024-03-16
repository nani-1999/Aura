// Copyright Na9i Studio


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraOverlay.h"
#include "GameFramework/PlayerController.h"


void AAuraHUD::InitOverlay(APlayerController* PC) {
	checkf(OverlayBP, TEXT("Unable to Find OverlayBP in AuraHUD"));

	Overlay = CreateWidget<UAuraOverlay>(GetWorld(), OverlayBP);
	Overlay->SetOwningPlayer(PC);
	Overlay->AddToViewport();

	if (Overlay) {
		UE_LOG(LogTemp, Warning, TEXT("%s Widget with Controller %s Created"), *PC->GetName(), *Overlay->GetName());
	}
}