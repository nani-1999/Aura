// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();

	//called when possessed by AController
	virtual void PossessedBy(AController* NewController) override;
	//called when playerstate is valid
	virtual void OnRep_PlayerState() override;

	// CombatInterface
	//since PlayerState's Level is the real one
	virtual int32 GetLvl() const override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

	void SetupAbilityActorInfo();
	void SetupOverlay();
};
