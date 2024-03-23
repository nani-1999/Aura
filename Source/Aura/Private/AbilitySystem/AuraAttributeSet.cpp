// Copyright Na9i Studio


#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemComponent.h" // @For GAMEPLAYATTRIBUTE_REPNOTIFY MACRO
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet() {
	//InitHealth(70.f);
	//InitMaxHealth(100.f);
	//InitMana(50.f);
	//InitMaxMana(100.f);

	//we can use GameplayEffect or DataTable of AttributeMetaData on AbilitySystemComponent, to set default attributeset's attribute values
}

// Boilerplate Code
// Multiplayer - Replication
void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Registering Attributes for Lifetime Replication
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}
void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}
void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}
void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldStrength);
}
void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldIntelligence);
}
void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilience, OldResilience);
}
void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldVigor);
}
void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, OldArmor);
}
void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPenetration, OldArmorPenetration);
}
void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BlockChance, OldBlockChance);
}
void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitChance, OldCriticalHitChance);
}
void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}
void UAuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}
void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthRegeneration, OldHealthRegeneration);
}
void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaRegeneration, OldManaRegeneration);
}
void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}
void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
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
void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) {
	Super::PreAttributeChange(Attribute, NewValue);

	UE_LOG(LogTemp, Warning, TEXT("PreAttributeChange"));
	// called by base or non-additive
	// clamping for attribute which have upper limit that changes
	// change for attribute that depend one other attribute that changes

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

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) {
	Super::PostGameplayEffectExecute(Data);

	UE_LOG(LogTemp, Warning, TEXT("PostGameplayEffectExecute"));
	// called when UGameplayEffect effects AbilitySystemComponent
	// won't be called by non-additive

	//FGameplayEffectModCallbackData has FGameplayEffectSpec
	//from spec we can get contexthandle

	const FGameplayEffectSpec EffectSpec = Data.EffectSpec;

	const FGameplayEffectContextHandle EffectContextHandle = EffectSpec.GetEffectContext();

	UAbilitySystemComponent* ASC = EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (ASC->AbilityActorInfo.IsValid() && ASC->AbilityActorInfo->AvatarActor.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("All Valid"));
	}
}
