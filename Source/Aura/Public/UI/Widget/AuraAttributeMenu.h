// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraAttributeMenu.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class AURA_API UAuraAttributeMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Button
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseBtn;

	// Widget
	//// Vital
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Vital_Health;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Vital_Mana;
	//// Primary
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Primary_Strength;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Primary_Intelligence;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Primary_Resilience;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Primary_Vigor;
	//// Secondary
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Secondary_Armor;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Secondary_ArmorPenetration;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Secondary_BlockChance;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Secondary_CriticalHitChance;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Secondary_CriticalHitDamage;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Secondary_CriticalHitResistance;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Secondary_HealthRegeneration;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Secondary_ManaRegeneration;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Secondary_MaxHealth;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Secondary_MaxMana;
};
