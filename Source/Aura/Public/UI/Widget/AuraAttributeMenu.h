// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraAttributeMenu.generated.h"


class UButton;
class UAuraLabel;

UCLASS()
class AURA_API UAuraAttributeMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	void InitializeAtomicWidget();
	void BindAtomicWidget();

	// Close
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;
	UFUNCTION()
	void CloseButton_Clicked();

	// Attribute Points
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> AttributePoints;
	// Primary
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> Strength;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> Intelligence;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> Resilience;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> Vigor;
	// Secondary
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> Armor;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> ArmorPenetration;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> BlockChance;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> CriticalHitChance;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> CriticalHitDamage;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> CriticalHitResistance;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> HealthRegeneration;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> ManaRegeneration;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> MaxHealth;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> MaxMana;
};
