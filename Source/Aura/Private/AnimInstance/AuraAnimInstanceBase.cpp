// Copyright Na9i Studio


#include "AnimInstance/AuraAnimInstanceBase.h"
#include "Character/AuraCharacterBase.h"

void UAuraAnimInstanceBase::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();

	if (AuraCharacterBase == nullptr) AuraCharacterBase = Cast<AAuraCharacterBase>(TryGetPawnOwner());
}

void UAuraAnimInstanceBase::UpdateAnimationProperties() {
	if (AuraCharacterBase == nullptr) AuraCharacterBase = Cast<AAuraCharacterBase>(TryGetPawnOwner());

	if (AuraCharacterBase) {
		Velocity = AuraCharacterBase->GetVelocity().Size2D();
	}
}