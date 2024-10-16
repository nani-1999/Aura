// Copyright Na9i Studio 2024.


#include "UI/WidgetManager/AuraOverlayManager.h"
#include "UI/Widget/AuraOverlay.h"
#include "GameFramework/PlayerController.h"
#include "GameMode/AuraPlayerState.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySystem/AbilitySystem/AuraAttributeSet.h"
#include "UI/Widget/AuraProgressBar.h"

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
	//// Atomic
	////// progressBar
	Overlay->Health_ProgressBar->SetValue(AuraAS->GetHealth());
	Overlay->Mana_ProgressBar->SetValue(AuraAS->GetMana());
	Overlay->Health_ProgressBar->SetMaxValue(AuraAS->GetMaxHealth());
	Overlay->Mana_ProgressBar->SetMaxValue(AuraAS->GetMaxMana());

	// Binding Overlay
	//// Atomic
	////// ProgressBar
	ASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetHealthAttribute()).AddUObject(this, &UAuraOverlayManager::HealthChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetManaAttribute()).AddUObject(this, &UAuraOverlayManager::ManaChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetMaxHealthAttribute()).AddUObject(this, &UAuraOverlayManager::MaxHealthChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetMaxManaAttribute()).AddUObject(this, &UAuraOverlayManager::MaxManaChanged);
}

void UAuraOverlayManager::HealthChanged(const FOnAttributeChangeData& Data) {
	Overlay->Health_ProgressBar->SetValue(Data.NewValue);
}
void UAuraOverlayManager::ManaChanged(const FOnAttributeChangeData& Data) {
	Overlay->Mana_ProgressBar->SetValue(Data.NewValue);
}
void UAuraOverlayManager::MaxHealthChanged(const FOnAttributeChangeData& Data) {
	Overlay->Health_ProgressBar->SetMaxValue(Data.NewValue);
}
void UAuraOverlayManager::MaxManaChanged(const FOnAttributeChangeData& Data) {
	Overlay->Mana_ProgressBar->SetMaxValue(Data.NewValue);
}