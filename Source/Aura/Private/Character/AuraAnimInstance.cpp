// Copyright Na9i Studio 2024.


#include "Character/AuraAnimInstance.h"

void UAuraAnimInstance::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();

	AuraAnimInstanceOwner = TryGetPawnOwner();
}

void UAuraAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (AuraAnimInstanceOwner == nullptr) {
		AuraAnimInstanceOwner = TryGetPawnOwner();
	}

	if (AuraAnimInstanceOwner) {
		Velocity = AuraAnimInstanceOwner->GetVelocity().Size2D();
	}
}