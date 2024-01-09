// Copyright Na9i Studio


#include "UI/Widget/AuraOverlay.h"
#include "UI/Widget/AuraProgressGlobe.h"
#include "Controller/AuraPlayerState.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "UI/Widget/AuraMessageWidget.h"


void UAuraOverlay::NativeConstruct() {
	InitSubWidgets();
	BindSubWidgets();
	BindMessages(); // not particularly in overlay, but can also do anywhere relevent

	UE_LOG(LogTemp, Warning, TEXT("NativeConstruct!!!!!!!"));
}

void UAuraOverlay::InitSubWidgets() {
	checkf(GetOwningPlayer(), TEXT("AuraOverlay unable to get Owning Player"));

	if (AAuraPlayerState* AuraPlayerState = GetOwningPlayerState<AAuraPlayerState>()) {

		if (UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AuraPlayerState->GetAttributeSet())) {

			// Initializing Sub Widgets
			float Health = AuraAttributeSet->GetHealth();
			float MaxHealth = AuraAttributeSet->GetMaxHealth();
			float Mana = AuraAttributeSet->GetMana();
			float MaxMana = AuraAttributeSet->GetMaxMana();

			HealthProgressGlobe->SetProgressGlobeValue(Health);
			HealthProgressGlobe->SetProgressGlobeMaxValue(MaxHealth);
			ManaProgressGlobe->SetProgressGlobeValue(Mana);
			ManaProgressGlobe->SetProgressGlobeMaxValue(MaxMana);
		}
	}
}

void UAuraOverlay::BindSubWidgets() {
	checkf(GetOwningPlayer(), TEXT("AuraOverlay unable to get Owning Player"));

	if (AAuraPlayerState* AuraPlayerState = GetOwningPlayerState<AAuraPlayerState>()) {

		UAuraAbilitySystemComponent* AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent());
		UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AuraPlayerState->GetAttributeSet());
		if (AuraAbilitySystemComponent && AuraAttributeSet) {

			// Binding Sub Widgets
			//AuraAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) { if (HealthProgressGlobe) HealthProgressGlobe->SetProgressGlobePercent(ValueChanged(Data.NewValue, Data.OldValue, HealthProgressGlobe->GetProgressGlobePercent())); });
			AuraAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UAuraOverlay::HealthChanged);
			AuraAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UAuraOverlay::MaxHealthChanged);
			AuraAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UAuraOverlay::ManaChanged);
			AuraAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UAuraOverlay::MaxManaChanged);
		}
	}
}
void UAuraOverlay::HealthChanged(const FOnAttributeChangeData& Data) {
	if (HealthProgressGlobe) HealthProgressGlobe->SetProgressGlobeValue(Data.NewValue);
}
void UAuraOverlay::MaxHealthChanged(const FOnAttributeChangeData& Data) {
	if (HealthProgressGlobe) HealthProgressGlobe->SetProgressGlobeMaxValue(Data.NewValue);
}
void UAuraOverlay::ManaChanged(const FOnAttributeChangeData& Data) {
	if (ManaProgressGlobe) ManaProgressGlobe->SetProgressGlobeValue(Data.NewValue);
}
void UAuraOverlay::MaxManaChanged(const FOnAttributeChangeData& Data) {
	if (ManaProgressGlobe) ManaProgressGlobe->SetProgressGlobeMaxValue(Data.NewValue);
}

void UAuraOverlay::BindMessages() {
	checkf(GetOwningPlayer(), TEXT("AuraOverlay unable to get Owning Player"));

	// Loading MessageDataTable
	MessageDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Script/Engine.DataTable'/Game/Blueprints/DataTables/DT_Message.DT_Message'")));

	// Biding Effect
	if (AAuraPlayerState* AuraPlayerState = GetOwningPlayerState<AAuraPlayerState>()) {
		UAuraAbilitySystemComponent* AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent());
		AuraAbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(this, &UAuraOverlay::EffectAppliedOnASC);
	}
}
void UAuraOverlay::EffectAppliedOnASC(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	UE_LOG(LogTemp, Warning, TEXT("AuraOverlay EffectApplied"));

	// Gettting All Tags
	FGameplayTagContainer TagContainter;
	EffectSpec.GetAllAssetTags(TagContainter);

	// Displaying Message Tags
	for (const FGameplayTag& Tag : TagContainter) {
		// Getting MessageTableRow of MessageTag
		FMessageTableRow* MessageTableRow = MessageDataTable->FindRow<FMessageTableRow>(Tag.GetTagName(), TEXT(""));
		if (MessageTableRow) CreateAndDisplayMessageWidget(MessageTableRow);
	}
}
void UAuraOverlay::CreateAndDisplayMessageWidget(FMessageTableRow* MessageTableRow) {
	if (MessageTableRow) {
		// WidgetClass
		TSubclassOf<UAuraMessageWidget> AuraMessageWidgetClass = MessageTableRow->MessageWidgetClass;
		// Creating Widget
		UAuraMessageWidget* AuraMessageWidget = CreateWidget<UAuraMessageWidget>(GetWorld(), AuraMessageWidgetClass);
		// Filling Data
		AuraMessageWidget->SetMessageTag(MessageTableRow->MessageTag);
		AuraMessageWidget->SetMessageIcon(MessageTableRow->MessageIcon);
		AuraMessageWidget->SetMessageText(MessageTableRow->MessageText);
		// Positioning
		FVector2D WidgetLocation = FVector2D::ZeroVector;
		int32 X, Y = 0;
		GetOwningPlayer()->GetViewportSize(X, Y);
		WidgetLocation.X = (X * 0.5f);
		WidgetLocation.Y = (Y * 0.6f);
		AuraMessageWidget->SetPositionInViewport(WidgetLocation);

		// Adding to Viewport
		AuraMessageWidget->AddToViewport();
	}
}
