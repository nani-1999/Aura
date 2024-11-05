// Copyright Na9i Studio 2024.


#include "GameMode/AuraPlayerController.h"
//#include "InputMappingContext.h" // UInputMappingContext
//#include "InputAction.h" // UInputAction
#include "DataAsset/AuraInputConfig.h"
#include "EnhancedInputSubsystems.h" // UEnhancedInputLocalPlayerSubsystem
#include "Input/AuraEnhancedInputComponent.h" // UAuraEnhancedInputComponent
#include "InputActionValue.h" // FInputActionValue
#include "Interface/HighlightInterface.h"

#include "Character/AuraCharacter.h"
#include "Aura/Nani/NaniUtility.h"

AAuraPlayerController::AAuraPlayerController() {
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay() {
	Super::BeginPlay();

	// Enhanced Input Subsystem
	// since we added "EnhancedInput" modules in Build.cs and EnhancedInput Class in project settings
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	//check(EnhancedInputSubsystem); //since we use replication we won't checking this

	// Input Mapping Context
	// adding mapping context to local player's input subsystem
	checkf(InputConfig, TEXT("AuraPlayerController | InputConfig is Invlaid"));
	if (EnhancedInputSubsystem)	EnhancedInputSubsystem->AddMappingContext(InputConfig->IMC_Aura, 0);

	// Mouse Cursor - Settings
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	// Mouse Cursor - Input Mode
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::PlayerTick(float DeltaTime) {
	Super::PlayerTick(DeltaTime);

	TraceUnderCursor();
}

void AAuraPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	// Enhanced Input Component
	//since we added "EnhancedInput" modules in Build.cs file, UInputComponent promotes to UEnhancedInputComponent
	//also Project Settings, Default Player Input Class is EnhancedPlayerInput and Default Input Component Class is EnhancedInputComponent
	//castChecked, we crash if casting fails
	//UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	//EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);

	// AuraEnhancedInputComponent
	UAuraEnhancedInputComponent* AuraEnhancedInputComponent = CastChecked<UAuraEnhancedInputComponent>(InputComponent);

	AuraEnhancedInputComponent->BindAction(InputConfig->IA_Move, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	AuraEnhancedInputComponent->BindActionsWithTag(InputConfig->AbilityInputActions, this, &AAuraPlayerController::AbilityInputPressed, &AAuraPlayerController::AbilityInputReleased);

	AuraEnhancedInputComponent->BindAction(InputConfig->IA_Test, ETriggerEvent::Started, this, &AAuraPlayerController::TestPressed);
}

void AAuraPlayerController::Move(const FInputActionValue& Value) {
	
	const FVector2D Value2D = Value.Get<FVector2D>();

	if (APawn* PossessedPawn = GetPawn()) {
		FRotator ControllerSurface = FRotator(0.f, GetControlRotation().Yaw, 0.f);
		FMatrix ControllerSurfaceMatrix = FRotationMatrix(ControllerSurface);

		FVector ForwardDirection = ControllerSurfaceMatrix.GetUnitAxis(EAxis::X);
		FVector RightDirection = ControllerSurfaceMatrix.GetUnitAxis(EAxis::Y);

		PossessedPawn->AddMovementInput(ForwardDirection, Value2D.X);
		PossessedPawn->AddMovementInput(RightDirection, Value2D.Y);
	}
}
void AAuraPlayerController::AbilityInputPressed(const FGameplayTag InputTag) {
	NANI_LOG(Warning, "%s Pressed", *InputTag.ToString());
}
void AAuraPlayerController::AbilityInputReleased(const FGameplayTag InputTag) {
	NANI_LOG(Warning, "%s Released", *InputTag.ToString());
}
void AAuraPlayerController::TestPressed() {
	NANI_LOG(Warning, "%s | TestPressed", *GetName());

	AAuraCharacter* AuraChar = GetPawn<AAuraCharacter>();
	AuraChar->Test();
}

//
//============================================ Cursor Trace ============================================
//
void AAuraPlayerController::TraceUnderCursor() {
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, CursorHit);

	TScriptInterface<IHighlightInterface> PreviousTracedHighlightInterface = TracedHighlightInterface;
	TracedHighlightInterface = CursorHit.GetActor();

	if (TracedHighlightInterface != PreviousTracedHighlightInterface) {
		if (PreviousTracedHighlightInterface) PreviousTracedHighlightInterface->UnHighlight();
		if (TracedHighlightInterface)  TracedHighlightInterface->Highlight();
	}
}