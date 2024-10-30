// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "AuraCharacterBase.generated.h"

class USkeletalMeshComponent;
class UAbilitySystemComponent;
class UAttributeSet;
class UAuraCharacterClassInfo;

UCLASS()
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

	// Getters
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	virtual UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual int32 GetCharacterLevel() const { return CharacterLevel; }
	const FGameplayTag& GetCharacterClass() const { return CharacterClass; }

protected:
	virtual void BeginPlay() override;

	// Weapon
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> Weapon;

	// AbilitySystem
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void InitAbilitySystem();

	// CharacterLevel
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults|Character")
	int32 CharacterLevel;

	// Character Class
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults|Character")
	FGameplayTag CharacterClass;

	// Character Class Info
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults|Character")
	TObjectPtr<UAuraCharacterClassInfo> CharacterClassInfo;

	// Attribute Defaults
	void InitAttributeDefaults(); 
};
