// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AuraCharacterBase.generated.h"

class USkeletalMeshComponent;
class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;

UCLASS()
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

	// Getters & Setters
	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	FORCEINLINE UAttributeSet* GetAttributeSet() { return AttributeSet; }

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
	TSubclassOf<UGameplayEffect> AttributeDefaults;
	void InitAttributeDefaults();
	
	//setupoverlay rename, try
};
