// Copyright Na9i Studio 2024.


#include "GameMode/AuraPlayerController.h"
//#include "InputMappingContext.h" // UInputMappingContext
//#include "InputAction.h" // UInputAction
#include "DataAsset/AuraInputConfig.h"
#include "EnhancedInputSubsystems.h" // UEnhancedInputLocalPlayerSubsystem
#include "Input/AuraEnhancedInputComponent.h" // UAuraEnhancedInputComponent
#include "InputActionValue.h" // FInputActionValue
#include "Interface/HighlightInterface.h"
#include "Components/SplineComponent.h"
#include "NavigationSystem.h" // UNavigationSystemV1
#include "NavigationPath.h" // UNavigationPath
#include "Character/AuraCharacter.h"

#include "DrawDebugHelpers.h"
#include "Aura/Nani/NaniUtility.h"

AAuraPlayerController::AAuraPlayerController() :
	bTestPressed{ false },
	bAbilityInputPressed{ false },
	bRMBPressed{ false },
	AcceptanceDistance{ 50.f },
	bAutoMove{ false }
{
	bReplicates = true;

	AutoMoveSpline = CreateDefaultSubobject<USplineComponent>(FName("AutoMoveSpline"));
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

	if (bAutoMove) AutoMove();
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

	// Test
	AuraEnhancedInputComponent->BindAction(InputConfig->IA_Test, ETriggerEvent::Started, this, &AAuraPlayerController::Test);
	AuraEnhancedInputComponent->BindAction(InputConfig->IA_Test, ETriggerEvent::Completed, this, &AAuraPlayerController::Test);
	// Move
	AuraEnhancedInputComponent->BindAction(InputConfig->IA_Move, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	// Ability
	AuraEnhancedInputComponent->BindActionsWithTag(InputConfig->AbilityInputActions, this, &AAuraPlayerController::AbilityInput);
	// RMB
	AuraEnhancedInputComponent->BindAction(InputConfig->IA_RMB, ETriggerEvent::Started, this, &AAuraPlayerController::RMB);
}

//
//============================================ Input ============================================
//
void AAuraPlayerController::Test(const FInputActionValue& Value) {
	bTestPressed = Value.Get<bool>();
	if (bTestPressed) {
		NANI_LOG(Warning, "%s | TestPressed", *GetName());
	}
	else {
		NANI_LOG(Warning, "%s | TestReleased", *GetName());
	}
	if (AAuraCharacter* AuraChar = GetPawn<AAuraCharacter>()) AuraChar->Test(bTestPressed);
}
void AAuraPlayerController::Move(const FInputActionValue& Value) {
	if (bAutoMove) StopAutoMove();

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
void AAuraPlayerController::AbilityInput(const FInputActionValue& Value, const FGameplayTag InputTag) {
	bAbilityInputPressed = Value.Get<bool>();

	if (AAuraCharacter* AuraChar = GetPawn<AAuraCharacter>()) AuraChar->AbilityInput(bAbilityInputPressed, InputTag);

	if (bAbilityInputPressed) {
		NANI_LOG(Warning, "AbilityInputPressed | %s", *InputTag.ToString());
	}
	else {
		NANI_LOG(Warning, "AbilityInputReleased | %s", *InputTag.ToString());
	}
}
void AAuraPlayerController::RMB(const FInputActionValue& Value) {
	bRMBPressed = Value.Get<bool>();

	if (bRMBPressed) {
		NANI_LOG(Warning, "RMBPressed");
		if (APawn* PossessedPawn = GetPawn()) UpdateSplineAndAutoMove();
	}
	else {
		NANI_LOG(Warning, "RMBReleased");
	}
}

//
//============================================ Cursor Trace ============================================
//
void AAuraPlayerController::TraceUnderCursor() {
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, CursorHit);
	AActor* CursorHitActor = CursorHit.GetActor();
	{
		// Highlight
		TScriptInterface<IHighlightInterface> PreviousTracedHighlightInterface = TracedHighlightInterface;
		TracedHighlightInterface = CursorHitActor;

		if (TracedHighlightInterface != PreviousTracedHighlightInterface) {
			if (PreviousTracedHighlightInterface) PreviousTracedHighlightInterface->UnHighlight();
			if (TracedHighlightInterface)  TracedHighlightInterface->Highlight();
		}
	}
}

//
//============================================ Auto Move ============================================
//
void AAuraPlayerController::UpdateSplineAndAutoMove() {
	APawn* PossessedPawn = GetPawn();
	FHitResult CursorHit;
	if (PossessedPawn && GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit)) {
		NavPathFinalDestination = CursorHit.Location;
		// getting Navigation Path Points b/w Cursor Hit Location and Possessed Pawn Location
		// NavBoundsVolume must in level floor
		// NavigationSystem in build.cs
		// AllowClientSideNavigation must be enabled in project settings
		if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, PossessedPawn->GetActorLocation(), NavPathFinalDestination)) {

			AutoMoveSpline->ClearSplinePoints();
			for (const FVector& Loc : NavPath->PathPoints) {
				DrawDebugPoint(GetWorld(), Loc, 10.f, FColor::Green, false, 3.f); // Debug
				AutoMoveSpline->AddSplinePoint(Loc, ESplineCoordinateSpace::World);
			}
			bAutoMove = true;
		}
		else {
			NANI_LOG(Error, "AuraPlayerController| Unable to Find NavPath");
		}
	}
}
void AAuraPlayerController::AutoMove() {
	APawn* PossessedPawn = GetPawn();
	if (PossessedPawn && bAutoMove) {
		FVector ClosestLocation = AutoMoveSpline->FindLocationClosestToWorldLocation(PossessedPawn->GetActorLocation(), ESplineCoordinateSpace::World); //since pawn has height and path points are on floor, so getting floor path point of pawn
		FVector ClosestDirection = AutoMoveSpline->FindDirectionClosestToWorldLocation(ClosestLocation, ESplineCoordinateSpace::World);
		PossessedPawn->AddMovementInput(ClosestDirection);

		//DrawDebugPoint(GetWorld(), ClosestLocation, 10.f, FColor::Red, false, 3.f); // Debug
		//DrawDebugPoint(GetWorld(), ClosestDirection, 10.f, FColor::Green, false, 3.f); // Debug
		//DrawDebugPoint(GetWorld(), PossessedPawn->GetActorLocation(), 10.f, FColor::Blue, false, 3.f); // Debug

		float ReachedDistance = (ClosestLocation - NavPathFinalDestination).Size(); // .GetSafeNormal() or .Size(), samething
		if (ReachedDistance <= AcceptanceDistance) {
			StopAutoMove();
		}
	}
	else {
		StopAutoMove();
	}
}
void AAuraPlayerController::StopAutoMove() {
	bAutoMove = false;
	NavPathFinalDestination = FVector::ZeroVector;
	AutoMoveSpline->ClearSplinePoints();
}