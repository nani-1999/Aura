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
	TObjectPtr<UButton> Close_Btn;

	// Widget
	//// Attribute Points
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> AttributePoints_Txt;

	//// Vital
	//UPROPERTY(meta = (BindWidget))
	//TObjectPtr<UTextBlock> Vital_Health_Txt;
	//UPROPERTY(meta = (BindWidget))
	//TObjectPtr<UTextBlock> Vital_Mana_Txt;

	//// Primary
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Primary_Strength_Txt;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Primary_Strength_Btn;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Primary_Intelligence_Txt;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Primary_Intelligence_Btn;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Primary_Resilience_Txt;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Primary_Resilience_Btn;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Primary_Vigor_Txt;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Primary_Vigor_Btn;

	//// Secondary
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Secondary_Armor_Txt;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Secondary_ArmorPenetration_Txt;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Secondary_BlockChance_Txt;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Secondary_CriticalHitChance_Txt;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Secondary_CriticalHitDamage_Txt;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Secondary_CriticalHitResistance_Txt;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Secondary_HealthRegeneration_Txt;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Secondary_ManaRegeneration_Txt;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Secondary_MaxHealth_Txt;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Secondary_MaxMana_Txt;
};
