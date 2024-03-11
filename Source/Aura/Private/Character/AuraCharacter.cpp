// Copyright Na9i Studio


#include "Character/AuraCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerState/AuraPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

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
}

void AAuraCharacter::OnRep_PlayerState() {
	Super::OnRep_PlayerState();

	SetupAbilityActorInfo();
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

	// @LOG
	UE_LOG(LogTemp, Warning, TEXT("%s Owner is %s"), *AuraPlayerState->GetName(), *AuraPlayerState->GetOwner()->GetName());
}