// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class USkeletalMeshComponent;
class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;

UCLASS()
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

	// AbilitySystemInterface
	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	FORCEINLINE UAttributeSet* GetAttributeSet() { return AttributeSet; }

	// CombatInterface
	FORCEINLINE virtual int32 GetLvl() const override { return Lvl; }

protected:
	// Weapon
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	// Ability System
	UPROPERTY(VisibleAnywhere, Category = "Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "Ability System")
	TObjectPtr<UAttributeSet> AttributeSet;

	// Attribute Defaults
	UPROPERTY(EditAnywhere, Category = "Ability System")
	TSubclassOf<UGameplayEffect> VitalAttributeDefaults;
	UPROPERTY(EditAnywhere, Category = "Ability System")
	TSubclassOf<UGameplayEffect> PrimaryAttributeDefaults;
	UPROPERTY(EditAnywhere, Category = "Ability System")
	TSubclassOf<UGameplayEffect> SecondaryAttributeDefaults;
	FORCEINLINE void InitAttributeDefaults() { ApplyEffectToSelf(SecondaryAttributeDefaults); ApplyEffectToSelf(PrimaryAttributeDefaults); ApplyEffectToSelf(VitalAttributeDefaults); }

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectBP);

	// Level
	UPROPERTY(VisibleAnywhere, Category = "Ability System")
	int32 Lvl = 1;
};
