// Copyright Na9i Studio


#include "Character/AuraCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerState/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Controller/AuraPlayerController.h"
#include "UI/HUD/AuraHUD.h"


AAuraCharacter::AAuraCharacter() {

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 420.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetUsingAbsoluteRotation(true); //sometimes inherits attached parent rotation
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->TargetArmLength = 450.f;
	CameraBoom->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

void AAuraCharacter::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);

	SetupAbilityActorInfo();
	SetupOverlay();
}

void AAuraCharacter::OnRep_PlayerState() {
	Super::OnRep_PlayerState();
	
	SetupAbilityActorInfo();
	//SetupOverlay(); //since replicating, we won't setup their overlay, though it causes error
}

void AAuraCharacter::SetupAbilityActorInfo() {
	//on possession by AController
	//setting up Ability System for this, from APlayerState
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
	// UAbilitySystemComponent, Owner vs Avatar
	// Owner Actor's Owner must be AController
	//APlayerState's Owner is automatically set to AController, no worry
	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);

	// AbilitySystemComponent Callbacks binding to Delegates
	//calling it here because, no early calling problem and calling right when needed
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->BindAppliedEffects();

	// Attributes Defaults
	InitAttributeDefaults();
}
void AAuraCharacter::SetupOverlay() {
	//since other player's controller player will be replicated, we have all their controllers
	if (AAuraPlayerController* AuraPC = GetController<AAuraPlayerController>()) {
		//since other player's HUD won't be replicated, so accessing their HUD and creating overlay may cause error
		if (AAuraHUD* AuraHUD = AuraPC->GetHUD<AAuraHUD>()) {
			AuraHUD->SetupOverlay(AuraPC);
		}
	}
}

int32 AAuraCharacter::GetLvl() const {
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetLvl();
}