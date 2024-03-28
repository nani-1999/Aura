// Copyright Na9i Studio


#include "UI/Widget/AuraOverlay.h"
#include "UI/Widget/AuraProgressBar.h"
#include "PlayerState/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/Widget/AuraMessage.h"
#include "Components/Button.h"
#include "UI/Widget/AuraAttributeMenu.h"

void UAuraOverlay::NativeOnInitialized() {
	Super::NativeOnInitialized();

	// Atomic
	InitializeAtomicWidget(); //replacing widget defaults
	BindAtomicWidget();

	// Messages
	BindMessages();

	// Attribute Menu
	AttributeMenuButton->OnClicked.AddDynamic(this, &UAuraOverlay::AttributeMenuButton_Clicked);
}

void UAuraOverlay::InitializeAtomicWidget() {
	AAuraPlayerState* AuraPS = GetOwningPlayerState<AAuraPlayerState>();
	UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AuraPS->GetAbilitySystemComponent());
	UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AuraPS->GetAttributeSet());

	HealthProgressBar->SetVal(AuraAS->GetHealth());
	HealthProgressBar->SetMaxVal(AuraAS->GetMaxHealth());
	ManaProgressBar->SetVal(AuraAS->GetMana());
	ManaProgressBar->SetMaxVal(AuraAS->GetMaxMana());
}
void UAuraOverlay::BindAtomicWidget() {
	AAuraPlayerState* AuraPS = GetOwningPlayerState<AAuraPlayerState>();
	UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AuraPS->GetAbilitySystemComponent());
	UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AuraPS->GetAttributeSet());

	AuraASC->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddUObject(this, &UAuraOverlay::HealthChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddUObject(this, &UAuraOverlay::MaxHealthChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(AuraAS->GetManaAttribute()).AddUObject(this, &UAuraOverlay::ManaChanged);
	AuraASC->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxManaAttribute()).AddUObject(this, &UAuraOverlay::MaxManaChanged);
}

void UAuraOverlay::HealthChanged(const FOnAttributeChangeData& Data) {
	HealthProgressBar->SetVal(Data.NewValue);
}
void UAuraOverlay::MaxHealthChanged(const FOnAttributeChangeData& Data) {
	HealthProgressBar->SetMaxVal(Data.NewValue);
}
void UAuraOverlay::ManaChanged(const FOnAttributeChangeData& Data) {
	ManaProgressBar->SetVal(Data.NewValue);
}
void UAuraOverlay::MaxManaChanged(const FOnAttributeChangeData& Data) {
	ManaProgressBar->SetMaxVal(Data.NewValue);
}

void UAuraOverlay::BindMessages() {
	AAuraPlayerState* AuraPS = GetOwningPlayerState<AAuraPlayerState>();
	UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AuraPS->GetAbilitySystemComponent());
	UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AuraPS->GetAttributeSet());

	AuraASC->OnAppliedEffectAssetTags.AddUObject(this, &UAuraOverlay::CreateAndDisplayMessages);
}
void UAuraOverlay::CreateAndDisplayMessages(FGameplayTagContainer& AssetTags) {
	if (AssetTags.IsEmpty()) return;

	for (const FGameplayTag& Tag : AssetTags) {
		FAuraMessageRow* MessageRow = Messages->FindRow<FAuraMessageRow>(Tag.GetTagName(), FString(""));
		if (MessageRow) {
			UAuraMessage* MessageWidget = CreateWidget<UAuraMessage>(GetWorld(), MessageRow->MessageBP);
			if (MessageWidget) {
				MessageWidget->DisplayMessage(Tag, MessageRow->Icon, MessageRow->Title, MessageRow->Detail);
			}
			else {
				UE_LOG(LogTemp, Error, TEXT("Unable to Create Message Widget in AuraOverlay"));
			}
		}
	}
}

void UAuraOverlay::AttributeMenuButton_Clicked() {
	UE_LOG(LogTemp, Warning, TEXT("AuraAttributeMenu Button Clicked"));
}