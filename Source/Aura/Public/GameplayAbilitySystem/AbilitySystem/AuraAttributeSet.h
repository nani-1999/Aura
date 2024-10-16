// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h" // @For Utility MACRO and GAMEPLAYATTRIBUTE_REPNOTIFY()
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UAuraAttributeSet();

	// for registering property replication
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	// Attributes
	//// Vital
	UPROPERTY(ReplicatedUsing = OnRep_Health)  //replication notify function binding, also attribute marked for replication
	FGameplayAttributeData Health;
	UPROPERTY(ReplicatedUsing = OnRep_Mana) 
	FGameplayAttributeData Mana;
	//// Primary
	UPROPERTY(ReplicatedUsing = OnRep_Strength) 
	FGameplayAttributeData Strength;
	UPROPERTY(ReplicatedUsing = OnRep_Intelligence) 
	FGameplayAttributeData Intelligence;
	UPROPERTY(ReplicatedUsing = OnRep_Resilience) 
	FGameplayAttributeData Resilience;
	UPROPERTY(ReplicatedUsing = OnRep_Vigor) 
	FGameplayAttributeData Vigor;
	//// Secondary
	UPROPERTY(ReplicatedUsing = OnRep_Armor) 
	FGameplayAttributeData Armor;
	UPROPERTY(ReplicatedUsing = OnRep_ArmorPenetration) 
	FGameplayAttributeData ArmorPenetration;
	UPROPERTY(ReplicatedUsing = OnRep_BlockChance) 
	FGameplayAttributeData BlockChance;
	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitChance) 
	FGameplayAttributeData CriticalHitChance;
	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitDamage) 
	FGameplayAttributeData CriticalHitDamage;
	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitResistance) 
	FGameplayAttributeData CriticalHitResistance;
	UPROPERTY(ReplicatedUsing = OnRep_HealthRegeneration) 
	FGameplayAttributeData HealthRegeneration;
	UPROPERTY(ReplicatedUsing = OnRep_ManaRegeneration) 
	FGameplayAttributeData ManaRegeneration;
	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth) 
	FGameplayAttributeData MaxHealth;
	UPROPERTY(ReplicatedUsing = OnRep_MaxMana) 
	FGameplayAttributeData MaxMana;

	// Multiplayer, Replication Notify
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
	UFUNCTION()
		void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

public:
	// MACRO Utilitiy Generator For 
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);
};
