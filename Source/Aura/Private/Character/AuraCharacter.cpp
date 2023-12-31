// Copyright Na9i Studio


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Controller/AuraPlayerController.h"
#include "Controller/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter() {

	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->TargetArmLength = 750.f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 420.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

// server
void AAuraCharacter::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);

	InitAbilitySystem();
}
// client
void AAuraCharacter::OnRep_PlayerState() {
	Super::OnRep_PlayerState();

	InitAbilitySystem();
}

void AAuraCharacter::InitAbilitySystem() {
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);

	// AbilitySystem
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this); // OwnerActor's Owner must be Controller

	// Effect Applied On ASC
	//AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(this, &AAuraCharacterBase::EffectAppliedOnASC); // to know gameplayeffects that are applied on abilitysystemcomponent, instants doesn't broadcase as explained in asc.h

	// OverlayWidget - Also this is where HUD initializes Overlay
	if (AAuraPlayerController* AuraPlayerController = GetController<AAuraPlayerController>()) {
		AAuraHUD* AuraHUD = AuraPlayerController->GetHUD<AAuraHUD>();
		AuraHUD->CreateOverlayWidget(AuraPlayerController);
	}
}
