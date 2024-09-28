// Copyright Na9i Studio 2024.


#include "Character/AuraEnemy.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy() {
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
	GetMesh()->CustomDepthStencilValue = CUSTOM_DEPTH_RED;
	Weapon->CustomDepthStencilValue = CUSTOM_DEPTH_RED;
}

void AAuraEnemy::BeginPlay() {
	Super::BeginPlay();

	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AAuraEnemy::Highlight() {
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}
void AAuraEnemy::UnHighlight() {
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}