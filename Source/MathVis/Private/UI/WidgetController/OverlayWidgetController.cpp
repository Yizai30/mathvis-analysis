// Copyright Yizai MathVis


#include "UI/WidgetController/OverlayWidgetController.h"

// #include "AbilitySystem/MVAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	// const UMVAttributeSet* MVAttributeSet = CastChecked<UMVAttributeSet>(AttributeSet);
	//
	// OnCurTimestampChanged.Broadcast(MVAttributeSet->GetCurTimestamp());
	// OnMaxTimestampChanged.Broadcast(MVAttributeSet->GetMaxTimestamp());
	// OnVertex1_XChanged.Broadcast(MVAttributeSet->GetVertex1_X());
	// OnVertex1_YChanged.Broadcast(MVAttributeSet->GetVertex1_Y());
	// OnVertex1_ZChanged.Broadcast(MVAttributeSet->GetVertex1_Z());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	// const UMVAttributeSet* MVAttributeSet = CastChecked<UMVAttributeSet>(AttributeSet);
	//
	// AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate
	// (MVAttributeSet->GetCurTimestampAttribute()).AddUObject(this, &UOverlayWidgetController::CurTimestampChanged);
	//
	// AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate
	// (MVAttributeSet->GetMaxTimestampAttribute()).AddUObject(this, &UOverlayWidgetController::MaxTimestampChanged);
	//
	// AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate
	// (MVAttributeSet->GetVertex1_XAttribute()).AddUObject(this, &UOverlayWidgetController::Vertex1_XChanged);
	//
	// AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate
	// (MVAttributeSet->GetVertex1_YAttribute()).AddUObject(this, &UOverlayWidgetController::Vertex1_YChanged);
	//
	// AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate
	// (MVAttributeSet->GetVertex1_ZAttribute()).AddUObject(this, &UOverlayWidgetController::Vertex1_ZChanged);
}

// void UOverlayWidgetController::CurTimestampChanged(const FOnAttributeChangeData& Data) const
// {
// 	// OnCurTimestampChanged.Broadcast(Data.NewValue);
// }
//
// void UOverlayWidgetController::MaxTimestampChanged(const FOnAttributeChangeData& Data) const
// {
// 	// OnMaxTimestampChanged.Broadcast(Data.NewValue);
// }
//
// void UOverlayWidgetController::Vertex1_XChanged(const FOnAttributeChangeData& Data) const
// {
// 	// OnVertex1_XChanged.Broadcast(Data.NewValue);
// }
//
// void UOverlayWidgetController::Vertex1_YChanged(const FOnAttributeChangeData& Data) const
// {
// 	// OnVertex1_YChanged.Broadcast(Data.NewValue);
// }
//
// void UOverlayWidgetController::Vertex1_ZChanged(const FOnAttributeChangeData& Data) const
// {
// 	// OnVertex1_ZChanged.Broadcast(Data.NewValue);
// }