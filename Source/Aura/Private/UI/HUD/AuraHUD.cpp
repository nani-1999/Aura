// Copyright Na9i Studio


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "Controller/AuraPlayerController.h"
#include "Controller/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"


void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS) {

	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class is not valid"));

	// OverlayWidget
	OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);

	// OverlayWidgetController
	//sicne Widget doens't automatically creates WidgetController itself
	UAuraWidgetController* OverlayWidgetController = NewObject<UAuraWidgetController>(this, UAuraWidgetController::StaticClass());
	FWidgetControllerParams WC_Params;
	WC_Params.PlayerController = PC;
	WC_Params.PlayerState = PS;
	WC_Params.AbilitySystemComponent = ASC;
	WC_Params.AttributeSet = AS;
	OverlayWidgetController->SetWidgetControllerParams(WC_Params);
	OverlayWidget->SetWidgetController(OverlayWidgetController);

	OverlayWidget->AddToViewport();
}
