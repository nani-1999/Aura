// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h" // @For FGameplayTag
#include "Engine/DataTable.h" // @For UTableRowBase
#include "AuraOverlay.generated.h"

class UAuraProgressBar;
struct FOnAttributeChangeData;
class UAuraMessage;
class UButton;
class UAuraAttributeMenu;

USTRUCT()
struct FAuraMessageRow : public FTableRowBase {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere)
	FText Title;

	UPROPERTY(EditAnywhere)
	FText Detail;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraMessage> MessageBP;
};

UCLASS()
class AURA_API UAuraOverlay : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	void InitializeAtomicWidget();
	void BindAtomicWidget();

	// Atomic Widgets
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraProgressBar> HealthProgressBar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraProgressBar> ManaProgressBar;

	// Messages
	void BindMessages();
	void CreateAndDisplayMessages(FGameplayTagContainer& AssetTags);
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> Messages;

	// Attribute Menu
	UPROPERTY(EditAnywhere, Category = "Attribute Menu")
	TSubclassOf<UAuraAttributeMenu> AttributeMenuBP;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> AttributeMenuButton;
	UFUNCTION()
	void AttributeMenuButton_Clicked();

	UFUNCTION()
	void AttributeMenuButton_Enable();

	// Callbacks
	void HealthChanged(const FOnAttributeChangeData& Data);
	void MaxHealthChanged(const FOnAttributeChangeData& Data);
	void ManaChanged(const FOnAttributeChangeData& Data);
	void MaxManaChanged(const FOnAttributeChangeData& Data);
};
