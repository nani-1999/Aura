// Copyright Na9i Studio


#include "UI/Widget/AuraOverlay.h"
#include "UI/Widget/AuraProgressGlobe.h"
#include "Controller/AuraPlayerState.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"


void UAuraOverlay::NativeConstruct() {
	InitSubWidgets();
	BindSubWidgets();
}

void UAuraOverlay::InitSubWidgets() {
	checkf(GetOwningPlayer(), TEXT("AuraOverlay unable to get Owning Player"));

	if (AAuraPlayerState* AuraPlayerState = GetOwningPlayerState<AAuraPlayerState>()) {

		if (UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AuraPlayerState->GetAttributeSet())) {

			UE_LOG(LogTemp, Warning, TEXT("NativeConstructed - AuraOverlay"));

			// Initializing Sub Widgets
			float Health = AuraAttributeSet->GetHealth();
			float MaxHealth = AuraAttributeSet->GetMaxHealth();
			float Mana = AuraAttributeSet->GetMana();
			float MaxMana = AuraAttributeSet->GetMaxMana();

			HealthProgressGlobe->SetProgressGlobePercent((MaxHealth != 0) ? (Health / MaxHealth) : 0.f);
			ManaProgressGlobe->SetProgressGlobePercent((MaxMana != 0) ? (Mana / MaxMana) : 0.f);
		}
	}
}
void UAuraOverlay::BindSubWidgets() {
	checkf(GetOwningPlayer(), TEXT("AuraOverlay unable to get Owning Player"));

	if (AAuraPlayerState* AuraPlayerState = GetOwningPlayerState<AAuraPlayerState>()) {

		UAuraAbilitySystemComponent* AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent());
		UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AuraPlayerState->GetAttributeSet());
		if (AuraAbilitySystemComponent && AuraAttributeSet) {

			// Binding Sub Widgets
			AuraAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UAuraOverlay::HealthChanged);
			AuraAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UAuraOverlay::MaxHealthChanged);
			AuraAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UAuraOverlay::ManaChanged);
			AuraAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UAuraOverlay::MaxManaChanged);
		}
	}
}

void UAuraOverlay::HealthChanged(const FOnAttributeChangeData& Data) {
	if (HealthProgressGlobe) HealthProgressGlobe->SetProgressGlobePercent(ValueChanged(Data.NewValue, Data.OldValue, HealthProgressGlobe->GetProgressGlobePercent()));
}
void UAuraOverlay::MaxHealthChanged(const FOnAttributeChangeData& Data) {
	if (HealthProgressGlobe) HealthProgressGlobe->SetProgressGlobePercent(MaxValueChanged(Data.NewValue, Data.OldValue, HealthProgressGlobe->GetProgressGlobePercent()));
}
void UAuraOverlay::ManaChanged(const FOnAttributeChangeData& Data) {
	if (ManaProgressGlobe) ManaProgressGlobe->SetProgressGlobePercent(ValueChanged(Data.NewValue, Data.OldValue, ManaProgressGlobe->GetProgressGlobePercent()));
}
void UAuraOverlay::MaxManaChanged(const FOnAttributeChangeData& Data) {
	if (ManaProgressGlobe) ManaProgressGlobe->SetProgressGlobePercent(MaxValueChanged(Data.NewValue, Data.OldValue, ManaProgressGlobe->GetProgressGlobePercent()));
}

float UAuraOverlay::ValueChanged(float NewValue, float OldValue, float Percent) {
	float MaxValue = OldValue / Percent;
	return (MaxValue != 0.f) ? (NewValue / MaxValue) : 0.f;
}
float UAuraOverlay::MaxValueChanged(float NewValue, float OldValue, float Percent) {
	float Value = Percent * OldValue;
	return (NewValue != 0.f) ? (Value / NewValue) : 0.f;
}
