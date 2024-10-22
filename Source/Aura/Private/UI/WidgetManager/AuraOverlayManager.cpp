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
#include "GameplayAbilitySystem/GameplayTags/AuraGameplayTags.h"

#include "Aura/Nani/NaniUtility.h"

void UAuraOverlayManager::SetupOverlay(UAuraOverlay* OverlayVal) {
	// saving Overlay here
	Overlay = OverlayVal;

	// Getting Overlay's PlayerController
	APlayerController* PC = Overlay->GetOwningPlayer();
	// Getting PlayerController's PlayerState
	AAuraPlayerState* AuraPS = PC->GetPlayerState<AAuraPlayerState>();
	// Getting PlayerState's AbilitySystem
	UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AuraPS->GetAbilitySystemComponent());
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
	
	//// Window
	////// Attribute Menu
	Overlay->OnAttributeMenuCreated.AddDynamic(this, &UAuraOverlayManager::InitAttributeMenu);
	//// Getting all data required by Overlay 
	AuraASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetHealthAttribute()).AddUObject(this, &UAuraOverlayManager::HealthChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetManaAttribute()).AddUObject(this, &UAuraOverlayManager::ManaChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetStrengthAttribute()).AddUObject(this, &UAuraOverlayManager::StrengthChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetIntelligenceAttribute()).AddUObject(this, &UAuraOverlayManager::IntelligenceChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetResilienceAttribute()).AddUObject(this, &UAuraOverlayManager::ResilienceChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetVigorAttribute()).AddUObject(this, &UAuraOverlayManager::VigorChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetArmorAttribute()).AddUObject(this, &UAuraOverlayManager::ArmorChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetArmorPenetrationAttribute()).AddUObject(this, &UAuraOverlayManager::ArmorPenetrationChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetBlockChanceAttribute()).AddUObject(this, &UAuraOverlayManager::BlockChanceChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetCriticalHitChanceAttribute()).AddUObject(this, &UAuraOverlayManager::CriticalHitChanceChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetCriticalHitDamageAttribute()).AddUObject(this, &UAuraOverlayManager::CriticalHitDamageChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetCriticalHitResistanceAttribute()).AddUObject(this, &UAuraOverlayManager::CriticalHitResistanceChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetHealthRegenerationAttribute()).AddUObject(this, &UAuraOverlayManager::HealthRegenerationChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetManaRegenerationAttribute()).AddUObject(this, &UAuraOverlayManager::ManaRegenerationChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetMaxHealthAttribute()).AddUObject(this, &UAuraOverlayManager::MaxHealthChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetMaxManaAttribute()).AddUObject(this, &UAuraOverlayManager::MaxManaChanged);
}

void UAuraOverlayManager::AppliedEffectAssetTags(const FGameplayTagContainer& Tags) {
	UE_LOG(LogTemp, Warning, TEXT("Getting Asset Tags in OverlayManager"));

	for (const FGameplayTag& Tag : Tags) {
		UE_LOG(LogTemp, Warning, TEXT("Applied GameplayEffect Asset TAgs: %s"), *Tag.ToString());
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
	Overlay->AttributeMenu->Vital_Health->SetText(FText::AsNumber(AuraAS->GetHealth()));
	Overlay->AttributeMenu->Vital_Mana->SetText(FText::AsNumber(AuraAS->GetMana()));
	Overlay->AttributeMenu->Primary_Strength->SetText(FText::AsNumber(AuraAS->GetStrength()));
	Overlay->AttributeMenu->Primary_Intelligence->SetText(FText::AsNumber(AuraAS->GetIntelligence()));
	Overlay->AttributeMenu->Primary_Resilience->SetText(FText::AsNumber(AuraAS->GetResilience()));
	Overlay->AttributeMenu->Primary_Vigor->SetText(FText::AsNumber(AuraAS->GetVigor()));
	Overlay->AttributeMenu->Secondary_Armor->SetText(FText::AsNumber(AuraAS->GetArmor()));
	Overlay->AttributeMenu->Secondary_ArmorPenetration->SetText(FText::AsNumber(AuraAS->GetArmorPenetration()));
	Overlay->AttributeMenu->Secondary_BlockChance->SetText(FText::AsNumber(AuraAS->GetBlockChance()));
	Overlay->AttributeMenu->Secondary_CriticalHitChance->SetText(FText::AsNumber(AuraAS->GetCriticalHitChance()));
	Overlay->AttributeMenu->Secondary_CriticalHitDamage->SetText(FText::AsNumber(AuraAS->GetCriticalHitDamage()));
	Overlay->AttributeMenu->Secondary_CriticalHitResistance->SetText(FText::AsNumber(AuraAS->GetCriticalHitResistance()));
	Overlay->AttributeMenu->Secondary_HealthRegeneration->SetText(FText::AsNumber(AuraAS->GetHealthRegeneration()));
	Overlay->AttributeMenu->Secondary_ManaRegeneration->SetText(FText::AsNumber(AuraAS->GetManaRegeneration()));
	Overlay->AttributeMenu->Secondary_MaxHealth->SetText(FText::AsNumber(AuraAS->GetMaxHealth()));
	Overlay->AttributeMenu->Secondary_MaxMana->SetText(FText::AsNumber(AuraAS->GetMaxMana()));
}

void UAuraOverlayManager::HealthChanged(const FOnAttributeChangeData& Data) {
	Overlay->Health_ProgressBar->SetValue(Data.NewValue);
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Vital_Health->SetText(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::ManaChanged(const FOnAttributeChangeData& Data) {
	Overlay->Mana_ProgressBar->SetValue(Data.NewValue);
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Vital_Mana->SetText(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::StrengthChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Primary_Strength->SetText(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::IntelligenceChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Primary_Intelligence->SetText(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::ResilienceChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Primary_Resilience->SetText(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::VigorChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Primary_Vigor->SetText(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::ArmorChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Secondary_Armor->SetText(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::ArmorPenetrationChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Secondary_ArmorPenetration->SetText(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::BlockChanceChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Secondary_BlockChance->SetText(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::CriticalHitChanceChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Secondary_CriticalHitChance->SetText(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::CriticalHitDamageChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Secondary_CriticalHitDamage->SetText(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::CriticalHitResistanceChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Secondary_CriticalHitResistance->SetText(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::HealthRegenerationChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Secondary_HealthRegeneration->SetText(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::ManaRegenerationChanged(const FOnAttributeChangeData& Data) {
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Secondary_ManaRegeneration->SetText(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::MaxHealthChanged(const FOnAttributeChangeData& Data) {
	Overlay->Health_ProgressBar->SetMaxValue(Data.NewValue);
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Secondary_MaxHealth->SetText(FText::AsNumber(Data.NewValue));
}
void UAuraOverlayManager::MaxManaChanged(const FOnAttributeChangeData& Data) {
	Overlay->Mana_ProgressBar->SetMaxValue(Data.NewValue);
	if (Overlay->AttributeMenu) Overlay->AttributeMenu->Secondary_MaxMana->SetText(FText::AsNumber(Data.NewValue));
}
