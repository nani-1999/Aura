// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController();

protected:
	virtual void BeginPlay() override;

	// Input
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* IMC_Aura;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* IA_Move;
};
