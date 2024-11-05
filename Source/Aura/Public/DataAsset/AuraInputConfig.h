// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AuraInputConfig.generated.h"

class UInputMappingContext;
class UInputAction;

USTRUCT()
struct FAuraInputAction {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputAction;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputActionTag;
};

UCLASS()
class AURA_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "InputMappingContext")
	TObjectPtr<UInputMappingContext> IMC_Aura;

	UPROPERTY(EditDefaultsOnly, Category = "InputActions|Movemento")
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "InputActions|Ability")
	TArray<FAuraInputAction> AbilityInputActions;

	//test
	UPROPERTY(EditDefaultsOnly, Category = "InputActions|Test")
	TObjectPtr<UInputAction> IA_Test;
};
