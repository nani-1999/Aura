// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h" // for FTableRowBase
#include "GameplayTagContainer.h" // for FGameplayTag, here because default struct contructing
#include "GameplayEffectTypes.h" // for FGameplayEffectSpec and FActiveGameplayEffectHandle
#include "AuraOverlay.generated.h"

class UAuraProgressGlobe;
struct FOnAttributeChangeData;
class UAuraMessageWidget;
class UAbilitySystemComponent;

USTRUCT()
struct FMessageTableRow : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere)
	UTexture2D* MessageIcon = nullptr;

	UPROPERTY(EditAnywhere)
	FText MessageText = FText();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraMessageWidget> MessageWidgetClass;

	// @TODO FVector2D MessageLocation()
};

UCLASS()
class AURA_API UAuraOverlay : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	void InitSubWidgets();
	void BindSubWidgets();
	void BindMessages();

	// Widgets
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraProgressGlobe> HealthProgressGlobe;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraProgressGlobe> ManaProgressGlobe;

	// Binds
	void HealthChanged(const FOnAttributeChangeData& Data); //ufunction not needed
	void MaxHealthChanged(const FOnAttributeChangeData& Data);
	void ManaChanged(const FOnAttributeChangeData& Data);
	void MaxManaChanged(const FOnAttributeChangeData& Data);
	void EffectAppliedOnASC(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

	// Helpers
	float ValueChanged(float NewValue, float OldValue, float Percent);
	float MaxValueChanged(float NewValue, float OldValue, float Percent);

	// Operations
	/** Creates, Adds to Viewport, plays animation and automatically destroyed */
	void CreateAndDisplayMessageWidget(FMessageTableRow* Message);

	// for Loading DataTable
	// PickupMessage DataTable
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> MessageDataTable; //must set UDataTable of FMessageTableRow
};
