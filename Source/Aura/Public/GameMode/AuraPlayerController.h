// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"

class UAuraInputConfig;
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

	// InputComponent
	virtual void SetupInputComponent() override;

	// Input Configuration
	UPROPERTY(EditDefaultsOnly, Category = "ClassDefaults|Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	// Input Binding
	void Move(const FInputActionValue& Value);
	void AbilityInputPressed(const FGameplayTag InputTag);
	void AbilityInputReleased(const FGameplayTag InputTag);
	//test
	void TestPressed();

	// TraceUnderCursor
	void TraceUnderCursor();
	TScriptInterface<IHighlightInterface> TracedHighlightInterface;
};
