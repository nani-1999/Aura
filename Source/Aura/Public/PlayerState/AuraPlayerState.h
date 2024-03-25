// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()
public:
	AAuraPlayerState();

	// AbilitySystemInterface
	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	// CombatInterface
	// don't use GetLevel(), is already in use
	FORCEINLINE virtual int32 GetLvl() const override { return Lvl; }

	// Multiplayer
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_Lvl(int32 OldLvl);

protected:
	// Ability System
	UPROPERTY(VisibleAnywhere, Category = "Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "Ability System")
	TObjectPtr<UAttributeSet> AttributeSet;

	// Level
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Lvl, Category = "Ability System")
	int32 Lvl = 1;
};
