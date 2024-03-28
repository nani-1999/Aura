// Copyright Na9i Studio


#include "UI/Widget/AuraAttributeMenu.h"
#include "Components/Button.h"
#include "UI/Widget/AuraLabel.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PlayerState/AuraPlayerState.h"

void UAuraAttributeMenu::NativeOnInitialized() {
	Super::NativeOnInitialized();

	CloseButton->OnClicked.AddDynamic(this, &UAuraAttributeMenu::CloseButton_Clicked);

	InitializeAtomicWidget(); //replacing widget defaults
	BindAtomicWidget();
}

void UAuraAttributeMenu::CloseButton_Clicked() {
	UE_LOG(LogTemp, Warning, TEXT("AuraAttributeMenu CloseButton Clicked"));
}

void UAuraAttributeMenu::InitializeAtomicWidget() {
	AAuraPlayerState* AuraPS = GetOwningPlayerState<AAuraPlayerState>();
	UAbilitySystemComponent* ASC = AuraPS->GetAbilitySystemComponent();
	UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AuraPS->GetAttributeSet());

	AttributePoints->SetLabelName("AttributePoints");
	AttributePoints->SetLabelValue(0.f);
	
	Strength->SetLabelName("Strength");
	Strength->SetLabelValue(AuraAS->GetStrength());
	Intelligence->SetLabelName("Intelligence");
	Intelligence->SetLabelValue(AuraAS->GetIntelligence());
	Resilience->SetLabelName("Resilience");
	Resilience->SetLabelValue(AuraAS->GetResilience());
	Vigor->SetLabelName("Vigor");
	Vigor->SetLabelValue(AuraAS->GetVigor());

	Armor->SetLabelName("Armor");
	Armor->SetLabelValue(AuraAS->GetArmor());
	ArmorPenetration->SetLabelName("Armor Penetration");
	ArmorPenetration->SetLabelValue(AuraAS->GetArmorPenetration());
	BlockChance->SetLabelName("Block Chance");
	BlockChance->SetLabelValue(AuraAS->GetBlockChance());
	CriticalHitChance->SetLabelName("Critical Hit Chance");
	CriticalHitChance->SetLabelValue(AuraAS->GetCriticalHitChance());
	CriticalHitDamage->SetLabelName("Critical Hit Damage");
	CriticalHitDamage->SetLabelValue(AuraAS->GetCriticalHitDamage());
	CriticalHitResistance->SetLabelName("Critical Hit Resistance");
	CriticalHitResistance->SetLabelValue(AuraAS->GetCriticalHitResistance());
	HealthRegeneration->SetLabelName("Health Regeneration");
	HealthRegeneration->SetLabelValue(AuraAS->GetHealthRegeneration());
	ManaRegeneration->SetLabelName("Mana Regeneration");
	ManaRegeneration->SetLabelValue(AuraAS->GetManaRegeneration());
	MaxHealth->SetLabelName("Max Health");
	MaxHealth->SetLabelValue(AuraAS->GetMaxHealth());
	MaxMana->SetLabelName("Max Mana");
	MaxMana->SetLabelValue(AuraAS->GetMaxMana());
}
void UAuraAttributeMenu::BindAtomicWidget() {

}