// Copyright Na9i Studio


#include "UI/Widget/AuraOverlay.h"
#include "UI/Widget/AuraProgressBar.h"
#include "PlayerState/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UAuraOverlay::NativeConstruct() {
	Super::NativeConstruct();

	InitializeAtomicWidget();
	BindAtomicWidget();
}
void UAuraOverlay::InitializeAtomicWidget() {
	AAuraPlayerState* AuraPS = GetOwningPlayerState<AAuraPlayerState>();
	UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AuraPS->GetAbilitySystemComponent());
	UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AuraPS->GetAttributeSet());

	HealthProgressBar->SetVal(AuraAS->GetHealth());
	HealthProgressBar->SetMaxVal(AuraAS->GetMaxHealth());
	ManaProgressBar->SetVal(AuraAS->GetMana());
	ManaProgressBar->SetMaxVal(AuraAS->GetMaxMana());
}
void UAuraOverlay::BindAtomicWidget() {
	AAuraPlayerState* AuraPS = GetOwningPlayerState<AAuraPlayerState>();
	UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AuraPS->GetAbilitySystemComponent());
	UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AuraPS->GetAttributeSet());

	AuraASC->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddUObject(this, &UAuraOverlay::HealthChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddUObject(this, &UAuraOverlay::MaxHealthChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(AuraAS->GetManaAttribute()).AddUObject(this, &UAuraOverlay::ManaChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxManaAttribute()).AddUObject(this, &UAuraOverlay::MaxManaChanged);
}

void UAuraOverlay::HealthChanged(const FOnAttributeChangeData& Data) {
	HealthProgressBar->SetVal(Data.NewValue);
}
void UAuraOverlay::MaxHealthChanged(const FOnAttributeChangeData& Data) {
	HealthProgressBar->SetMaxVal(Data.NewValue);
}
void UAuraOverlay::ManaChanged(const FOnAttributeChangeData& Data) {
	HealthProgressBar->SetVal(Data.NewValue);
}
void UAuraOverlay::MaxManaChanged(const FOnAttributeChangeData& Data) {
	HealthProgressBar->SetMaxVal(Data.NewValue);
}