// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraOverlay.generated.h"

class UAuraProgressBar;
class UButton;
class UAuraAttributeMenu;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAuraWidgetDelegate, UUserWidget*, AuraWidget);

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
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> AttributeMenu_Btn;
	UPROPERTY(EditAnywhere, Category = "ClassDefaults | AttributeMenu")
	TSubclassOf<UAuraAttributeMenu> AttributeMenuBP;
	UPROPERTY()
	TObjectPtr<UAuraAttributeMenu> AttributeMenu;
	FAuraWidgetDelegate OnAttributeMenuCreated;

protected:
	UFUNCTION()
	void AttributeMenu_Btn_Clicked();
	UFUNCTION()
	void AttributeMenu_CloseBtn_Clicked();
};
