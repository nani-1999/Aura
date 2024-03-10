// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AuraAnimInstanceBase.generated.h"

class AAuraCharacterBase;

UCLASS()
class AURA_API UAuraAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	// Pawn Owner
	UPROPERTY()
	AAuraCharacterBase* AuraCharacterBase;

public:
	// Properties
	UPROPERTY(BlueprintReadOnly)
	float Velocity;
	UPROPERTY(BlueprintReadOnly)
	bool bIsFalling;
	UPROPERTY(BlueprintReadOnly)
	bool bIsAccelerating;
};
