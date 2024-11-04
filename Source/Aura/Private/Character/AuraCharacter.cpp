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

int32 AAuraCharacter::GetCharacterLevel() const {
	return GetPlayerState<AAuraPlayerState>()->GetCharacterLevel();
}

void AAuraCharacter::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);

	NANI_LOG(Warning, "%s | PossessedBy()", *GetName());

	// AbilitySystem
	InitAbilitySystem();

	// HUD
	InitLocalPlayerHUD();
}
void AAuraCharacter::OnRep_PlayerState() {
	Super::OnRep_PlayerState();

	// HUD
	InitLocalPlayerHUD();
}

void AAuraCharacter::InitAbilitySystem() {

	// this will only be executed on authority

	if (!HasAuthority()) return;

	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	AAuraPlayerState* AuraPS = GetPlayerState<AAuraPlayerState>();

	ASC->InitAbilityActorInfo(AuraPS, this);

	// calling super's version after InitAbilityActorInfo is set
	Super::InitAbilitySystem();
}

void AAuraCharacter::InitLocalPlayerHUD() {

	// this will only be executed on local player

	if (!IsLocallyControlled()) return;

	//Overlay
	// setting up Overlay locally controlled player
	APlayerController* PC = GetController<APlayerController>();
	PC->GetHUD<AAuraHUD>()->InitOverlay(PC);
	NANI_LOG(Warning, "%s | Initializing Overlay Locally", *GetName());

	// @Important, this will only be triggered in Servers
	// even if you bind it in client and apply effect on client, it worn't trigger
	//ASC->OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &AAuraCharacter::EffectAppliedToSelf);
}