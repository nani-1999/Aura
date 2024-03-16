// Copyright Na9i Studio


#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemComponent.h" // @For GAMEPLAYATTRIBUTE_REPNOTIFY MACRO
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet() {
	InitHealth(70.f);
	InitMaxHealth(100.f);
	InitMana(50.f);
	InitMaxMana(100.f);
}

// Boilerplate Code
// Multiplayer - Replication
void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Registering Attributes for Lifetime Replication
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}
void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}
void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}
void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}
void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) {
	Super::PreAttributeChange(Attribute, NewValue);

	UE_LOG(LogTemp, Warning, TEXT("PostAttributeChange"));
	// called by base or non-additive
	// clamping for attribute which have upper limit that changes

	if (Attribute == GetHealthAttribute()) {
		//no clamping here, since non-additive effects won't be applied on Health
	}
	if (Attribute == GetMaxHealthAttribute()) {
		float HealthVal = GetHealth();
		if (HealthVal > NewValue) {
			SetHealth(NewValue);
		}
	}
	if (Attribute == GetManaAttribute()) {
	}
	if (Attribute == GetMaxManaAttribute()) {
		float ManaVal = GetMana();
		if (ManaVal > NewValue) {
			SetMana(NewValue);
		}
	}
}
void UAuraAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const {
	Super::PreAttributeBaseChange(Attribute, NewValue);

	UE_LOG(LogTemp, Warning, TEXT("PreAttributeBaseChange"));
	// called by base only
	// clamping for attributes which have upper limit

	if (Attribute == GetHealthAttribute()) {
		NewValue = FMath::Clamp<float>(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetMaxHealthAttribute()) {
		//no clamping here, since MaxHealth doesn't have upper limit
	}
	if (Attribute == GetManaAttribute()) {
		NewValue = FMath::Clamp<float>(NewValue, 0.f, GetMaxMana());
	}
	if (Attribute == GetMaxManaAttribute()) {
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) {
	Super::PostGameplayEffectExecute(Data);

	UE_LOG(LogTemp, Warning, TEXT("PostGameplayEffectExecute"));
}
