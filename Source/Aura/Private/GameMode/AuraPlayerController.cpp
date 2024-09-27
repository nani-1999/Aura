// Copyright Na9i Studio 2024.


#include "GameMode/AuraPlayerController.h"
#include "InputMappingContext.h" // UInputMappingContext
#include "InputAction.h" // UInputAction
#include "EnhancedInputSubsystems.h" // UEnhancedInputLocalPlayerSubsystem

AAuraPlayerController::AAuraPlayerController() {
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay() {
	Super::BeginPlay();

	// Cursor and InputMode
	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);


	// Assigned Assets Checking
	check(IMC_Aura);
	check(IA_Move);

	// Setting Up InputSubsystem
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(EnhancedInputSubsystem);
	EnhancedInputSubsystem->AddMappingContext(IMC_Aura, 0);
}