// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraOverlay.generated.h"

class UAuraProgressBar;
class UButton;
class UAuraAttributeMenu;
class USizeBox;
class UAuraMessage;

UCLASS()
class AURA_API UAuraOverlay : public UUserWidget
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAuraWidgetDelegate);

protected:
	virtual void NativeOnInitialized() override;

public:
	// Atomic
	//// ProgressBar
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraProgressBar> Health_ProgressBar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraProgressBar> Mana_ProgressBar;
	//// Message
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults | Message")
	TSubclassOf<UAuraMessage> ItemMessageBP;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> ItemMessage_Slot;

	// Window
	//// Attribute Menu
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> AttributeMenu_Slot;
	UPROPERTY()
	TObjectPtr<UAuraAttributeMenu> AttributeMenu;
	FAuraWidgetDelegate OnAttributeMenuCreated; // need for initializing beginning values

protected:
	// Window
	//// Attribute Menu
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> AttributeMenu_Btn;
	UFUNCTION()
	void AttributeMenu_Btn_Clicked();
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults | AttributeMenu")
	TSubclassOf<UAuraAttributeMenu> AttributeMenuBP;
	UFUNCTION()
	void AttributeMenu_CloseBtn_Clicked();
};
