// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "GameplayTagContainer.h"
#include "AuraCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();

	// Getters
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;

	/** server only, called when a controller possess this pawn */
	virtual void PossessedBy(AController* NewController) override;
	/** client only, called when a playerstate is ready and replicating */
	virtual void OnRep_PlayerState() override;

	// Input
	//// Ability
	void AbilityInput(const bool bAbilityInputPressed, const FGameplayTag& InputTag);
	//// Test
	void Test(const bool bTestPressed);

protected:
	virtual void BeginPlay() override;

	// Components
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> FollowCamera;

	// AbilitySystem
	virtual void InitAbilitySystem() override;

	// Character Level
	virtual int32 GetCharacterLevel() const override;

	// HUD
	void InitLocalPlayerHUD();
};
