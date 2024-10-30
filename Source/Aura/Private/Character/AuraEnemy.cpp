// Copyright Na9i Studio 2024.


#include "Character/AuraEnemy.h"
#include "GameplayAbilitySystem/AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameplayAbilitySystem/AbilitySystem/AuraAttributeSet.h"

AAuraEnemy::AAuraEnemy() {

	// custom depth
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
	GetMesh()->CustomDepthStencilValue = CUSTOM_DEPTH_RED;
	Weapon->CustomDepthStencilValue = CUSTOM_DEPTH_RED;

	// AbilitySystem
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>(FName("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>(FName("AttributeSet"));
}

void AAuraEnemy::BeginPlay() {
	Super::BeginPlay();

	// custom depth
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);

	// AbilitySystem
	InitAbilitySystem();
}

void AAuraEnemy::Highlight() {
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}
void AAuraEnemy::UnHighlight() {
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AAuraEnemy::InitAbilitySystem() {

	// AbilityActorInfo
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	// calling super's version after InitAbilityActorInfo is set
	Super::InitAbilitySystem();
}