// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IHighlightInterface;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;

	// Input
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> IMC_Aura;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> IA_Move;

	// InputComponent
	virtual void SetupInputComponent() override;

	// Input Binding
	void Move(const FInputActionValue& Value);

	// TraceUnderCursor
	void TraceUnderCursor();
	TScriptInterface<IHighlightInterface> TracedHighlightInterface;
};
