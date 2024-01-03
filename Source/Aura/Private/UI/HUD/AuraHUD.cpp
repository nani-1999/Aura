// Copyright Na9i Studio


#include "UI/HUD/AuraHUD.h"
#include "GameFramework/PlayerController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/Widget/AuraOverlay.h"


void AAuraHUD::CreateOverlayWidget(APlayerController* PC) {
	checkf(OverlayWidgetClass, TEXT("Unable to Create Overlay Widget due to invalid OverlayWidgetClass"));

	OverlayWidget = CreateWidget<UAuraOverlay>(GetWorld(), OverlayWidgetClass);

	OverlayWidget->SetOwningPlayer(PC);
	OverlayWidget->AddToViewport(); //this will trigger nativeconstruct, it will initvalues and bindvalues
}
