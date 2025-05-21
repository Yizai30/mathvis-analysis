// Copyright Yizai MathVis


#include "UI/WidgetController/MVWidgetController.h"

void UMVWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UMVWidgetController::BroadcastInitialValues()
{
}

void UMVWidgetController::BindCallbacksToDependencies()
{
}