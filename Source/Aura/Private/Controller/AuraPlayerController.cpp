// Copyright Na9i Studio


#include "Controller/AuraPlayerController.h"
#include "InputMappingContext.h" // @For UInputMappingContext
#include "InputAction.h" // @For UInputAction
#include "EnhancedInputSubsystems.h" // @For UEnhancedInputLocalPlayerSubsystem
#include "EnhancedInputComponent.h" // @For UEnhancedInputComponent

AAuraPlayerController::AAuraPlayerController() {
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay() {
	Super::BeginPlay();

	check(AuraContext);

	// Enhanced Input Subsystem
	//since we added "EnhancedInput" modules in Build.cs
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(EnhancedInputSubsystem);

	// Input Mapping Context
	EnhancedInputSubsystem->AddMappingContext(AuraContext, 0);

	// Mouse Cursor - Settings
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// Mouse Cursor - Input Mode
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	// Enhanced Input Component
	//since we added "EnhancedInput" modules in Build.cs file, UInputComponent promotes to UEnhancedInputComponent
	//also Project Settings, Default Player Input Class is EnhancedPlayerInput and Default Input Component Class is EnhancedInputComponent
	//castChecked, we crash if casting fails
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& Value) {
	// InputAction Value
	const FVector2D InputAxisValue = Value.Get<FVector2D>();

	// Surface and Its Matrix
	FRotator Surface = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	FMatrix SurfaceMatrix = FRotationMatrix(Surface);

	FVector ForwardDirection = SurfaceMatrix.GetUnitAxis(EAxis::X);
	FVector RightDirection = SurfaceMatrix.GetUnitAxis(EAxis::Y);

	// Possessed Pawn
	if (APawn* PossessedPawn = GetPawn<APawn>()) {
		// MovementComponent
		PossessedPawn->AddMovementInput(ForwardDirection, InputAxisValue.Y);
		PossessedPawn->AddMovementInput(RightDirection, InputAxisValue.X);
	}
}
