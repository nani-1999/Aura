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

protected:
	TObjectPtr<AAuraCharacterBase> AuraCharacterBase;

public:
	UFUNCTION(BlueprintCallable)
	virtual void UpdateAnimationProperties();

	UPROPERTY(BlueprintReadOnly)
	float Velocity;
};
