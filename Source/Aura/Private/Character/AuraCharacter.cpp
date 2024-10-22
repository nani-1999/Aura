// Copyright Na9i Studio 2024.


#include "Character/AuraCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayAbilitySystem/AbilitySystem/AuraAbilitySystemComponent.h"
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

	NANI_LOG(Warning, "%s | PossessedBy()", *GetName());

	// AbilitySystem
	InitAbilitySystem();
}
void AAuraCharacter::OnRep_PlayerState() {
	Super::OnRep_PlayerState();

	NANI_LOG(Warning, "%s | OnRep_PlayerState()", *GetName());

	// AbilitySystem
	InitAbilitySystem();
}

void AAuraCharacter::InitAbilitySystem() {

	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	AAuraPlayerState* AuraPS = GetPlayerState<AAuraPlayerState>();
	APlayerController* PC = GetController<APlayerController>();

	// AbilityActorInfo
	ASC->InitAbilityActorInfo(AuraPS, this);

	//Binding Applied Effect Tags for Assets Tags
	//if (HasAuthority()) {
	//	NANI_LOG(Warning, "%s | BindingAssetTags in Authority", *GetName());
	//	Cast<UAuraAbilitySystemComponent>(ASC)->BindAppliedEffectTags();
	//}
	//else if (IsLocallyControlled()) {
	//	NANI_LOG(Warning, "%s | Binding AssetTags in Local", *GetName());
	//	Cast<UAuraAbilitySystemComponent>(ASC)->BindAppliedEffectTags();
	//}

	// Overlay
	if (IsLocallyControlled()) {
		NANI_LOG(Warning, "%s is LocallyControlled", *GetName());
		PC->GetHUD<AAuraHUD>()->InitOverlay(PC);
	}
}