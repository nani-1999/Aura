// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "AuraOverlay.generated.h"

class UAuraProgressBar;
class UButton;
class UAuraAttributeMenu;
class USizeBox;
class UAuraMessage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAuraWidgetDelegate);

USTRUCT()
struct FMessageTableRow : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults")
	TSubclassOf<UAuraMessage> MessageClass;

	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults")
	TObjectPtr<UTexture2D> IconTexture;

	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults")
	FText TitleText;

	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults")
	FText DetailText;
};

UCLASS()
class AURA_API UAuraOverlay : public UUserWidget
{
	GENERATED_BODY()

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
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> PickUpMessage_Slot;
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults | Message")
	TObjectPtr<UDataTable> MessageDataTable;
	void DisplayMessage(const FName MessageName);

	// Window
	//// Attribute Menu
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USizeBox> AttributeMenu_Slot;
	UPROPERTY()
	TObjectPtr<UAuraAttributeMenu> AttributeMenu;
	FAuraWidgetDelegate OnAttributeMenuCreated;

protected:
	// Window
	//// Attribute Menu
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> AttributeMenu_Btn;
	UFUNCTION()
	void AttributeMenu_Btn_Clicked();
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults | AttributeMenu")
	TSubclassOf<UAuraAttributeMenu> AttributeMenuClass;
	UFUNCTION()
	void AttributeMenu_CloseBtn_Clicked();
};
