// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class USkeletalMeshComponent;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class AURA_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

	// Getters
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }
	virtual UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* Weapon;

	// AbilitySystem
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
