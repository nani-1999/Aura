// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AAuraPlayerState();

	// Getters
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	FORCEINLINE int32 GetCharacterLevel() const { return CharacterLevel; }

	// for registering property replication
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// AbilitySystem
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	// Character Level
	UPROPERTY(ReplicatedUsing = OnRep_CharacterLevel)
	int32 CharacterLevel;

	UFUNCTION()
	void OnRep_CharacterLevel(const int32& OldCharacterLevel) const {}
};
