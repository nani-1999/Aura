// Copyright Na9i Studio 2024.


#include "Character/AuraCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameMode/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

#include "Aura/Nani/NaniUtility.h"

AAuraCharacter::AAuraCharacter() {

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->TargetArmLength = 750.f;
	CameraBoom->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(FName("CameraComponent"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);


	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	CharacterMovementComponent->RotationRate = FRotator(0.f, 420.f, 0.f);
	CharacterMovementComponent->bOrientRotationToMovement = true;
}

void AAuraCharacter::BeginPlay() {
	Super::BeginPlay();

}

UAbilitySystemComponent* AAuraCharacter::GetAbilitySystemComponent() const {
	return GetPlayerState<AAuraPlayerState>()->GetAbilitySystemComponent();
}
UAttributeSet* AAuraCharacter::GetAttributeSet() const {
	return GetPlayerState<AAuraPlayerState>()->GetAttributeSet();
}

void AAuraCharacter::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);

	// AbilitySystem
	InitAbilitySystem();
}
void AAuraCharacter::OnRep_PlayerState() {
	Super::OnRep_PlayerState();

	// AbilitySystem
	InitAbilitySystem();
}

void AAuraCharacter::InitAbilitySystem() {
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	AAuraPlayerState* AuraPS = GetPlayerState<AAuraPlayerState>();\

	// AbilityActorInfo
	ASC->InitAbilityActorInfo(AuraPS, this);

	// Overlay
	if (IsLocallyControlled()) {
		AAuraHUD* AuraHUD = GetController<APlayerController>()->GetHUD<AAuraHUD>();
		NANI_LOG(Warning, "%s is LocallyControlled", *GetName());
	}
}