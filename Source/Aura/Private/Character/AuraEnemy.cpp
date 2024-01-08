// Copyright Na9i Studio


#include "Character/AuraEnemy.h"
#include "Aura/Aura.h" //for custom depth
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraEnemy::AAuraEnemy() {
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	GetMesh()->CustomDepthStencilValue = CUSTOM_DEPTH_RED; //CUSTOM_DEPTH_RED defined in aura.h
	Weapon->CustomDepthStencilValue = CUSTOM_DEPTH_RED;

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

}

void AAuraEnemy::HighlightActor() {
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}
void AAuraEnemy::UnHighlightActor() {
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AAuraEnemy::BeginPlay() {
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	//AuraASC->OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &AAuraCharacterBase::EffectAppliedOnASC); // instants doesn't broadcase as explained in asc.h
}
