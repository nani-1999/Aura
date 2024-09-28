// Copyright Na9i Studio 2024.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interface/HighlightInterface.h"
#include "AuraEnemy.generated.h"

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IHighlightInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();

protected:
	virtual void BeginPlay() override;

	virtual void Highlight() override;
	virtual void UnHighlight() override;
};
