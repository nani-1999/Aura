// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAsset/AuraInputConfig.h"
#include "GameplayTagContainer.h"
#include "AuraEnhancedInputComponent.generated.h"

UCLASS()
class AURA_API UAuraEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindActionsWithTag(const TArray<FAuraInputAction>& InputActions, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc);
};

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void UAuraEnhancedInputComponent::BindActionsWithTag(const TArray<FAuraInputAction>& InputActions, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc) {

	for (const FAuraInputAction& AuraIA : InputActions) {
		checkf(AuraIA.InputAction, TEXT("AuraEnhancedInputComponent | InputAction is Invalid"));
		checkf(AuraIA.InputActionTag.IsValid(), TEXT("AuraEnhancedInputComponent | Invalid Tag when binding InputAction"));

		if (PressedFunc) {
			BindAction(AuraIA.InputAction, ETriggerEvent::Started, Object, PressedFunc, AuraIA.InputActionTag);
		}
		if (ReleasedFunc) {
			BindAction(AuraIA.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, AuraIA.InputActionTag);
		}
	}
}