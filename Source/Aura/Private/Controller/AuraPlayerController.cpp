// Copyright Na9i Studio


#include "Controller/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Interaction/EnemyInterface.h"
#include "Character/AuraCharacter.h"


AAuraPlayerController::AAuraPlayerController() {
	bReplicates = true;

}

void AAuraPlayerController::BeginPlay() {
	Super::BeginPlay();

	// adding context to subsystem
	check(AuraContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);

	// Cursor Settings
	bShowMouseCursor = true; //mouse cursor display
	DefaultMouseCursor = EMouseCursor::Default; //mouse shape
	FInputModeGameAndUI InputModeData; //input to effect on game and ui
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); //not locking mouse cursor to the viewport/window
	InputModeData.SetHideCursorDuringCapture(false); //do not hide cursor while click on viewport/window
	SetInputMode(InputModeData);
}

void AAuraPlayerController::PlayerTick(float DeltaTime) {
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	EnhancedInputComponent->BindAction(TestAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Test);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue) {
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>(); //WS- Y | AD - X

	FRotator ControllerRotation = GetControlRotation();
	FRotator ControllerSurface = FRotator(0.f, ControllerRotation.Yaw, 0.f);

	FVector ForwardDirection = FRotationMatrix(ControllerSurface).GetUnitAxis(EAxis::X);
	FVector RightDirection = FRotationMatrix(ControllerSurface).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>()) {
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace() {
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit); //since this is a trace, make sure visiblity collision is set to block, to get hitresult actor
	if (!CursorHit.bBlockingHit) return;

	IEnemyInterface* CurrentHitEnemy = Cast<IEnemyInterface>(CursorHit.GetActor());
	if (CurrentHitEnemy) {
		if (CurrentHitEnemy != PreviousHitEnemy) {
			if (PreviousHitEnemy) PreviousHitEnemy->UnHighlightActor();
			PreviousHitEnemy = CurrentHitEnemy;
			CurrentHitEnemy->HighlightActor();
		}
	}
	else if (PreviousHitEnemy) {
		PreviousHitEnemy->UnHighlightActor();
		PreviousHitEnemy = nullptr;
	}
}

// Test
void AAuraPlayerController::Test() {
	UE_LOG(LogTemp, Warning, TEXT("Test Triggered"));
}