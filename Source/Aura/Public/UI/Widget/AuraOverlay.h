// Copyright Na9i Studio

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraOverlay.generated.h"

class UAuraProgressBar;
struct FOnAttributeChangeData;

UCLASS()
class AURA_API UAuraOverlay : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	void InitializeAtomicWidget();
	void BindAtomicWidget();

	// Atomic Widgets
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraProgressBar> HealthProgressBar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UAuraProgressBar> ManaProgressBar;

	// Callbacks
	void HealthChanged(const FOnAttributeChangeData& Data);
	void MaxHealthChanged(const FOnAttributeChangeData& Data);
	void ManaChanged(const FOnAttributeChangeData& Data);
	void MaxManaChanged(const FOnAttributeChangeData& Data);
};
