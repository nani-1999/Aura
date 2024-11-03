// Copyright Na9i Studio 2024.


#include "UI/WidgetManager/AuraOverlayManager.h"
#include "UI/Widget/AuraOverlay.h"
#include "GameFramework/PlayerController.h"
#include "GameMode/AuraPlayerState.h"
#include "GameplayAbilitySystem/AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameplayAbilitySystem/AbilitySystem/AuraAttributeSet.h"
#include "UI/Widget/AuraProgressBar.h"
#include "UI/Widget/AuraAttributeMenu.h"
#include "Components/TextBlock.h"
#include "UI/Widget/AuraLabel.h"

#include "Aura/Nani/NaniUtility.h"

void UAuraOverlayManager::SetupOverlay(UAuraOverlay* OverlayVal) {
	// saving Overlay here
	Overlay = OverlayVal;

	// Getting Overlay's PlayerController
	APlayerController* PC = Overlay->GetOwningPlayer();
	// Getting PlayerController's PlayerState
	AAuraPlayerState* AuraPS = PC->GetPlayerState<AAuraPlayerState>();
	// Getting PlayerState's AbilitySystem
	UAbilitySystemComponent* ASC = AuraPS->GetAbilitySystemComponent();
	UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AuraPS->GetAttributeSet());

	// Initializing Overlay
	//
	//// Atomic
	////// Globe Progress Bar
	Overlay->Health_ProgressBar->SetValue(AuraAS->GetHealth());
	Overlay->Mana_ProgressBar->SetValue(AuraAS->GetMana());
	Overlay->Health_ProgressBar->SetMaxValue(AuraAS->GetMaxHealth());
	Overlay->Mana_ProgressBar->SetMaxValue(AuraAS->GetMaxMana());

	// Binding Overlay
	//
	//// Atomic
	////// Message
	Cast<UAuraAbilitySystemComponent>(ASC)->OnAppliedEffectAssetTags.AddDynamic(this, &UAuraOverlayManager::AppliedEffectAssetTags);
	//// Window
	////// Attribute Menu
	Overlay->OnAttributeMenuCreated.AddDynamic(this, &UAuraOverlayManager::InitAttributeMenu);

	
	// Getting all data required by Overlay 
	ASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetHealthAttribute()).AddUObject(this, &UAuraOverlayManager::HealthChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetManaAttribute()).AddUObject(this, &UAuraOverlayManager::ManaChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetStrengthAttribute()).AddUObject(this, &UAuraOverlayManager::StrengthChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetIntelligenceAttribute()).AddUObject(this, &UAuraOverlayManager::IntelligenceChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetResilienceAttribute()).AddUObject(this, &UAuraOverlayManager::ResilienceChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetVigorAttribute()).AddUObject(this, &UAuraOverlayManager::VigorChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetArmorAttribute()).AddUObject(this, &UAuraOverlayManager::ArmorChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetArmorPenetrationAttribute()).AddUObject(this, &UAuraOverlayManager::ArmorPenetrationChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetBlockChanceAttribute()).AddUObject(this, &UAuraOverlayManager::BlockChanceChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetCriticalHitChanceAttribute()).AddUObject(this, &UAuraOverlayManager::CriticalHitChanceChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetCriticalHitDamageAttribute()).AddUObject(this, &UAuraOverlayManager::CriticalHitDamageChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetCriticalHitResistanceAttribute()).AddUObject(this, &UAuraOverlayManager::CriticalHitResistanceChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetHealthRegenerationAttribute()).AddUObject(this, &UAuraOverlayManager::HealthRegenerationChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetManaRegenerationAttribute()).AddUObject(this, &UAuraOverlayManager::ManaRegenerationChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetMaxHealthAttribute()).AddUObject(this, &UAuraOverlayManager::MaxHealthChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetMaxManaAttribute()).AddUObject(this, &UAuraOverlayManager::MaxManaChanged);
}

void UAuraOverlayManager::AppliedEffectAssetTags(const FGameplayTagContainer& Tags) {
	for (const FGameplayTag& Tag : Tags) {
		Overlay->DisplayMessage(*Tag.ToString());
	}
}

void UAuraOverlayManager::InitAttributeMenu() {
	// Getting Overlay's PlayerController
	APlayerController* PC = Overlay->GetOwningPlayer();
	// Getting PlayerController's PlayerState
	AAuraPlayerState* AuraPS = PC->GetPlayerState<AAuraPlayerState>();
	// Getting PlayerState's AbilitySystem
	UAbilitySystemComponent* ASC = AuraPS->GetAbilitySystemComponent();
	UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AuraPS->GetAttributeSet());

	// Initializing Attribute Menu
	Overlay->AttributeMenu->Primary_Strength->SetLabelValue(FText::AsNumber(AuraAS->GetStrength()));
	Overlay->AttributeMenu->Primary_Intelligence->SetLabelValue(FText::AsNumber(AuraAS->GetIntelligence()));
	Overlay->AttributeMenu->Primary_Resilience->SetLabelValue(FText::AsNumber(AuraAS->GetResilience()));
	Overlay->AttributeMenu->Primary_Vigor->SetLabelValue(FText::AsNumber(AuraAS->GetVigor()));
	Overlay->AttributeMenu->Secondary_Armor->SetLabelValue(FText::AsNumber(AuraAS->GetArmor()));
	Overlay->AttributeMenu->Secondary_ArmorPenetration->SetLabelValue(FText::AsNumber(AuraAS->GetArmorPenetration()));
	Overlay->AttributeMenu->Secondary_BlockChance->SetLabelValue(FText::AsNumber(AuraAS->GetBlockChance()));
	Overlay->AttributeMenu->Secondary_CriticalHitChance->SetLabelValue(FText::AsNumber(AuraAS->GetCriticalHitChance()));
	Overlay->AttributeMenu->Secondary_CriticalHitDamage->SetLabelValue(FText::AsNumber(AuraAS->GetCriticalHitDamage()));
	Overlay->AttributeMenu->Secondary_CriticalHitResistance->SetLabelValue(FText::AsNumber(AuraAS->GetCriticalHitResistance()));
	Overlay->AttributeMenu->Secondary_HealthRegeneration->SetLabelValue(FText::AsNumber(AuraAS->GetHealthRegeneration()));
	Overlay->AttributeMenu->Secondary_ManaRegeneration->SetLabelValue(FText::AsNumber(AuraAS->GetManaRegeneration()));
	Overlay->AttributeMenu->Secondary_MaxHealth->SetLabelValue(FText::AsNumber(AuraAS->GetMaxHealth()));
	Overlay->AttributeMenu->Secondary_MaxMana->SetLabelValue(FText::AsNumber(AuraAS->GetMaxMana()));
}

void UAuraOverlayManager::HealthChanged(const FOnAttributeChangeData& Data) {
	Overlay->Health_ProgressBar->SetValue(Data.NewValue);
}
void UAuraOverlayManager::ManaChanged(const FOnAttributeChangeData& Data) {
	Overlay->Mana_ProgressBar->SetValue(Data.NewValue);
}
void UAuraOverlayManager::StrengthChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Primary_Strength->SetLabelValue(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::IntelligenceChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Primary_Intelligence->SetLabelValue(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::ResilienceChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Primary_Resilience->SetLabelValue(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::VigorChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Primary_Vigor->SetLabelValue(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::ArmorChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Secondary_Armor->SetLabelValue(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::ArmorPenetrationChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Secondary_ArmorPenetration->SetLabelValue(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::BlockChanceChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Secondary_BlockChance->SetLabelValue(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::CriticalHitChanceChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Secondary_CriticalHitChance->SetLabelValue(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::CriticalHitDamageChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Secondary_CriticalHitDamage->SetLabelValue(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::CriticalHitResistanceChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Secondary_CriticalHitResistance->SetLabelValue(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::HealthRegenerationChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Secondary_HealthRegeneration->SetLabelValue(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::ManaRegenerationChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Secondary_ManaRegeneration->SetLabelValue(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::MaxHealthChanged(const FOnAttributeChangeData& Data) {
	Overlay->Health_ProgressBar->SetMaxValue(Data.NewValue);
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Secondary_MaxHealth->SetLabelValue(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::MaxManaChanged(const FOnAttributeChangeData& Data) {
	Overlay->Mana_ProgressBar->SetMaxValue(Data.NewValue);
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Secondary_MaxMana->SetLabelValue(FText::AsNumber(Data.NewValue));
}
