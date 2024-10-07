// Copyright Na9i Studio 2024.


#include "Character/AuraCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameMode/AuraPlayerState.h"

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

void AAuraCharacter::InitAbilitySystemInfo() {

	AbilitySystemComponent->InitAbilityActorInfo(GetPlayerState(), this);
}