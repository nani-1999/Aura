// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"

class UAuraInputConfig;
struct FInputActionValue;
class IHighlightInterface;
class USplineComponent;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;

	// InputComponent
	virtual void SetupInputComponent() override;

	// Input Configuration
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults|Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	// Input Binding
	//// Test
	void Test(const FInputActionValue& Value);
	bool bTestPressed;
	//// Move
	void Move(const FInputActionValue& Value);
	//// Ability
	void AbilityInput(const FInputActionValue& Value, const FGameplayTag InputTag);
	bool bAbilityInputPressed;
	//// RMB
	void RMB(const FInputActionValue& Value);
	bool bRMBPressed;

	// TraceUnderCursor
	void TraceUnderCursor();
	//// Highlight
	TScriptInterface<IHighlightInterface> TracedHighlightInterface;

	// Auto Move
	UPROPERTY()
	TObjectPtr<USplineComponent> AutoMoveSpline;
	void UpdateSplineAndAutoMove();
	FVector NavPathFinalDestination;
	float AcceptanceDistance;
	bool bAutoMove;
	void AutoMove();
	void StopAutoMove();
};