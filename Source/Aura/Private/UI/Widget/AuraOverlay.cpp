// Copyright Na9i Studio 2024.


#include "UI/Widget/AuraOverlay.h"
#include "Components/Button.h"
#include "UI/Widget/AuraProgressBar.h"
#include "UI/Widget/AuraAttributeMenu.h"
#include "Components/SizeBox.h"
#include "UI/Widget/AuraMessage.h"
//#include "Components/NamedSlot.h"

void UAuraOverlay::NativeOnInitialized() {
	Super::NativeOnInitialized();

	// Attribute Menu
	AttributeMenu_Btn->OnClicked.AddDynamic(this, &UAuraOverlay::AttributeMenu_Btn_Clicked);
	AttributeMenu_Btn->SetIsEnabled(true);
}

void UAuraOverlay::DisplayMessage(const FName MessageName) {
	// Getting Message Assets for Displaying Message Widget on Overlay
	// can use DataAsset which we can have a function to get Specific TableRow based on MessageName, i.e., Message.Quest, Message.Pickup
	// @Important, use DataAsset with TMap<Enum, Value> for large data structure, for efficiency, to avoiding string comparision 
	FMessageTableRow* MessageTR = MessageDataTable->FindRow<FMessageTableRow>(MessageName, TEXT(""));

	// we crash if we can't find assets for displaying message
	checkf(MessageTR, TEXT("AuraOverlayManager | Message TableRow is invalid"));

	// checking if the have Assets with that MessageName
	if (MessageTR) {
		// clearning the Slot before adding Message
		PickUpMessage_Slot->ClearChildren();

		// creating Message
		UAuraMessage* AuraM = UAuraMessage::CreateMessage(GetWorld(), MessageTR->MessageClass, MessageTR->IconTexture, MessageTR->TitleText, MessageTR->DetailText);

		// adding the created Message to the Slot
		// the message will destroy itself after completing animation
		PickUpMessage_Slot->AddChild(AuraM);
	}
}

void UAuraOverlay::AttributeMenu_Btn_Clicked() {
	checkf(AttributeMenuClass, TEXT("AttributeMenuClass is Invalid | in AuraOverlay.cpp | ObjectName: %s"), *GetName());

	UE_LOG(LogTemp, Warning, TEXT("AttributeMenu | Widget Created"));

	// disabling attribute menu
	AttributeMenu_Btn->SetIsEnabled(false);

	// creating attribute menu
	AttributeMenu = CreateWidget<UAuraAttributeMenu>(GetWorld(), AttributeMenuClass);
	// binding close button of that attribute menu
	AttributeMenu->Close_Btn->OnClicked.AddDynamic(this, &UAuraOverlay::AttributeMenu_CloseBtn_Clicked);
	// broadcasting that attribute is ready for initialization
	OnAttributeMenuCreated.Broadcast();

	// adding to slot
	AttributeMenu_Slot->AddChild(AttributeMenu);
}
void UAuraOverlay::AttributeMenu_CloseBtn_Clicked() {
	AttributeMenu->RemoveFromParent();
	AttributeMenu = nullptr; // making sure reference count reaches 0, for garbage collection
	AttributeMenu_Btn->SetIsEnabled(true);
}
