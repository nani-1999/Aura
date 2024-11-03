// Copyright Na9i Studio 2024.


#include "UI/Widget/AuraAttributeMenu.h"
#include "Components/Button.h"
#include "UI/Widget/AuraLabel.h"

void UAuraAttributeMenu::NativeOnInitialized() {
	Super::NativeOnInitialized();

	// Close Button
	Close_Btn->SetIsEnabled(true);

	// Attribute Points
	AttributePoints->SetLabelName(FText::FromString("Attribute Points"));

	// Attributes
	//// Primary
	Primary_Strength->SetLabelName(FText::FromString("Strength"));
	Primary_Intelligence->SetLabelName(FText::FromString("Intelligence"));
	Primary_Resilience->SetLabelName(FText::FromString("Resilience"));
	Primary_Vigor->SetLabelName(FText::FromString("Vigor"));
	//// Secondary
	Secondary_Armor->SetLabelName(FText::FromString("Armor"));
	Secondary_ArmorPenetration->SetLabelName(FText::FromString("Armor Penetration"));
	Secondary_BlockChance->SetLabelName(FText::FromString("Block Chance"));
	Secondary_CriticalHitChance->SetLabelName(FText::FromString("Critical Hit Chance"));
	Secondary_CriticalHitDamage->SetLabelName(FText::FromString("Critical Hit Damage"));
	Secondary_CriticalHitResistance->SetLabelName(FText::FromString("Critical Hit Resistance"));
	Secondary_HealthRegeneration->SetLabelName(FText::FromString("Health Regeneration"));
	Secondary_ManaRegeneration->SetLabelName(FText::FromString("Mana Regeneration"));
	Secondary_MaxHealth->SetLabelName(FText::FromString("Max Health"));
	Secondary_MaxMana->SetLabelName(FText::FromString("Max Mana"));
}