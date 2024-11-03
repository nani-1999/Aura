// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraAttributeMenu.generated.h"

class UTextBlock;
class UButton;
class UAuraLabel;

UCLASS()
class AURA_API UAuraAttributeMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

public:
	virtual void RemoveFromParent() override { UE_LOG(LogTemp, Warning, TEXT("AttributeMenu | Widget Removed")); Super::RemoveFromParent(); }

	// Close Button
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Close_Btn;

	// Widget
	//// Attribute Points
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> AttributePoints;

	//// Primary
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> Primary_Strength;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> Primary_Intelligence;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> Primary_Resilience;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> Primary_Vigor;

	//// Secondary
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> Secondary_Armor;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> Secondary_ArmorPenetration;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> Secondary_BlockChance;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> Secondary_CriticalHitChance;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> Secondary_CriticalHitDamage;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> Secondary_CriticalHitResistance;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> Secondary_HealthRegeneration;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> Secondary_ManaRegeneration;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> Secondary_MaxHealth;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraLabel> Secondary_MaxMana;
};
