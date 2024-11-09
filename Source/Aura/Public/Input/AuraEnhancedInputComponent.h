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
	template<class UserClass, typename FuncType>
	void BindActionsWithTag(const TArray<FAuraInputAction>& InputActions, UserClass* Object, FuncType Func);
};

template<class UserClass, typename FuncType>
void UAuraEnhancedInputComponent::BindActionsWithTag(const TArray<FAuraInputAction>& InputActions, UserClass* Object, FuncType Func) {

	for (const FAuraInputAction& AuraIA : InputActions) {
		// checking
		checkf(AuraIA.InputAction, TEXT("AuraEnhancedInputComponent | InputAction is Invalid"));
		checkf(AuraIA.InputActionTag.IsValid(), TEXT("AuraEnhancedInputComponent | Invalid Tag when binding InputAction"));
		
		// Binding with Tag
		BindAction(AuraIA.InputAction, ETriggerEvent::Started, Object, Func, AuraIA.InputActionTag);
		BindAction(AuraIA.InputAction, ETriggerEvent::Completed, Object, Func, AuraIA.InputActionTag);
	}
}