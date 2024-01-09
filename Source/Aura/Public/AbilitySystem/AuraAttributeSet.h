// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h" // must be here
#include "GameplayEffectExtension.h" // for FGameplayEffectModCallbackData
#include "AuraAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class AbilitySystemComponent;

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAuraAttributeSet();

	// must, Keep Track of Attributes
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Primary Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes")
	FGameplayAttributeData Resilience;

	// Vital Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes") //Max values will never be zero
	FGameplayAttributeData MaxHealth;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;

	// Getters Setters and more
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);

	// Attribute Replication Notifies from Server
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	UFUNCTION()
	void OnRep_Resilienceconst FGameplayAttributeData& OldResilience) const;

	// Attribute change
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	// post GameplayEffect
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override; 
};
