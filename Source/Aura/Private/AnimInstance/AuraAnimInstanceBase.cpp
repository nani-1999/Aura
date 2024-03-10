// Copyright Na9i Studio


#include "AnimInstance/AuraAnimInstanceBase.h"
#include "Character/AuraCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAuraAnimInstanceBase::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();

	AuraCharacterBase = Cast<AAuraCharacterBase>(TryGetPawnOwner());
}

void UAuraAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (AuraCharacterBase == nullptr) AuraCharacterBase = Cast<AAuraCharacterBase>(TryGetPawnOwner());
	
	if (AuraCharacterBase) {
		Velocity = AuraCharacterBase->GetVelocity().Size2D();
		bIsFalling = AuraCharacterBase->GetCharacterMovement()->IsFalling();
		bIsAccelerating = AuraCharacterBase->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f;
	}
}