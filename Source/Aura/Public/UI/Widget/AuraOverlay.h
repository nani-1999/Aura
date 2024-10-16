// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraOverlay.generated.h"

class UAuraProgressBar;
class UButton;
class UAuraAttributeMenu;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAuraWidgetDelegate);

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

	// Window
	//// Attribute Menu
	UPROPERTY()
	TObjectPtr<UAuraAttributeMenu> AttributeMenu;
	FAuraWidgetDelegate OnAttributeMenuCreated; // need for initializing beginning values

protected:
	// Window
	//// Attribute Menu
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> AttributeMenu_Btn;
	UPROPERTY(EditAnywhere, Category = "ClassDefaults | AttributeMenu")
	TSubclassOf<UAuraAttributeMenu> AttributeMenuBP;
	UFUNCTION()
	void AttributeMenu_Btn_Clicked();
	UFUNCTION()
	void AttributeMenu_CloseBtn_Clicked();
};
