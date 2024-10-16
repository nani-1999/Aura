// Copyright Na9i Studio 2024.


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraOverlay.h"
#include "UI/WidgetManager/AuraOverlayManager.h"

#include "Aura/Nani/NaniUtility.h"

void AAuraHUD::InitOverlay(APlayerController* PC) {
	// checking for blueprint
	checkf(OverlayBP != nullptr/* && OverlayManagerBP != NULL*/, TEXT("OverlayBP is Invalid, in AuraHUD.cpp, ObjectName: %s"), *GetName());
	// checking if Overlay already existed
	checkf(Overlay == nullptr && OverlayManager == nullptr, TEXT("Overlay already Exist, in AuraHUD.cpp, ObjectName: %s"), *GetName());

	if (Overlay != nullptr) NANI_LOG(Warning, "Overlay Already Exist");

	// Overlay
	Overlay = CreateWidget<UAuraOverlay>(GetWorld(), OverlayBP);
	// OverlayManager
	OverlayManager = NewObject<UAuraOverlayManager>(Overlay);
	OverlayManager->SetupOverlay(Overlay);
	Overlay->AddToViewport();
}