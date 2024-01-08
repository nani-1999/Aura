// Copyright Na9i Studio


#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"

UAuraAttributeSet::UAuraAttributeSet() {
	InitHealth(40.f);
	InitMaxHealth(100.f);
	InitMana(70.f);
	InitMaxMana(100.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// must, Replication Notify settings
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always); // REPNOTIFY_Always, doesn't matter if value is same or changed keep notifying. REPNOTIFY_OnChanged, only notify when value changed
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::OnRep_Health(FGameplayAttributeData& OldHealth) const { //called from server when replicated, oldvalue vs newvalue, so we can keep track with oldvalue to rollback just-in-case
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}
void UAuraAttributeSet::OnRep_MaxHealth(FGameplayAttributeData& OldMaxHealth) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}
void UAuraAttributeSet::OnRep_Mana(FGameplayAttributeData& OldMana) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}
void UAuraAttributeSet::OnRep_MaxMana(FGameplayAttributeData& OldMaxMana) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) {
	// @TODO: clamp health when additive MaxHealth is over

	//called before an attribute additive(non-base) is being changed
	//this is the function that changes attributes additive
	//we can do custom calucation for each attribute here
	if (Attribute == GetHealthAttribute()) {
		NewValue = FMath::Clamp<float>(NewValue, 0.f, GetMaxHealth()); //BaseHealth = Base, CurrentHealth = Total, NonAdditiveHealth = Total - Base
	}
	else if (Attribute == GetManaAttribute()) {
		NewValue = FMath::Clamp<float>(NewValue, 0.f, GetMaxMana());
	}

	// after very pre calucation
	Super::PreAttributeChange(Attribute, NewValue);
}
void UAuraAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const {
	//called before an attribute base is being changed
	//this is the function that changes attributes base
	//we can do custom calucation for each attribute here
	if (Attribute == GetHealthAttribute()) {
		NewValue = FMath::Clamp<float>(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute == GetManaAttribute()) {
		NewValue = FMath::Clamp<float>(NewValue, 0.f, GetMaxMana());
	}

	// after very pre calucation
	Super::PreAttributeBaseChange(Attribute, NewValue);
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) {
	Super::PostGameplayEffectExecute(Data);

	//called when UGameplayEffect effects AbilitySystemComponent
	//FGameplayEffectModCallbackData has all kinds of information like GameplayEffectSpec, context(source), target(instigator)

	FGameplayEffectSpec GameplayEffectSpec = Data.EffectSpec;
	FGameplayEffectContextHandle GameplayEffectContextHandle = GameplayEffectSpec.GetContext();
	UAbilitySystemComponent* ASC = GameplayEffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	//checking ASC and its Avatar
	if (IsValid(ASC) && ASC->AbilityActorInfo.IsValid() && ASC->AbilityActorInfo->AvatarActor.IsValid()) {
		//UE_LOG(LogTemp, Warning, TEXT("Hello Information"));
		return;
	}
}
