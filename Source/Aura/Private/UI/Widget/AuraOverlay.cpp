// Copyright Na9i Studio 2024.


#include "UI/Widget/AuraOverlay.h"
#include "Components/Button.h"
#include "UI/Widget/AuraProgressBar.h"
#include "UI/Widget/AuraAttributeMenu.h"
#include "Components/SizeBox.h"

void UAuraOverlay::NativeOnInitialized() {
	Super::NativeOnInitialized();

	// Attribute Menu
	AttributeMenu_Btn->OnClicked.AddDynamic(this, &UAuraOverlay::AttributeMenu_Btn_Clicked);
	AttributeMenu_Btn->SetIsEnabled(true);
}

void UAuraOverlay::AttributeMenu_Btn_Clicked() {
	checkf(AttributeMenuClass, TEXT("AttributeMenuClass is Invalid | in AuraOverlay.cpp | ObjectName: %s"), *GetName());

	AttributeMenu_Btn->SetIsEnabled(false);

	AttributeMenu = CreateWidget<UAuraAttributeMenu>(GetWorld(), AttributeMenuClass);
	AttributeMenu->Close_Btn->OnClicked.AddDynamic(this, &UAuraOverlay::AttributeMenu_CloseBtn_Clicked);
	OnAttributeMenuCreated.Broadcast(); //telling WidgetManager, its ready for initialization
}
void UAuraOverlay::AttributeMenu_CloseBtn_Clicked() {
	AttributeMenu->RemoveFromParent();
	AttributeMenu_Btn->SetIsEnabled(true);
}