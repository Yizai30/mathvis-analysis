// Copyright Yizai MathVis

#pragma once

#include "CoreMinimal.h"
// #include "AbilitySystem/MVAttributeSet.h"
#include "UI/WidgetController/MVWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurTimestampChangedSignature, float, NewCurTimestamp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxTimestampChangedSignature, float, NewMaxTimestamp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVertex1_XChangedSignature, float, NewVertex1_X);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVertex1_YChangedSignature, float, NewVertex1_Y);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVertex1_ZChangedSignature, float, NewVertex1_Z);

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class MATHVIS_API UOverlayWidgetController : public UMVWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnCurTimestampChangedSignature OnCurTimestampChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxTimestampChangedSignature OnMaxTimestampChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnVertex1_XChangedSignature OnVertex1_XChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnVertex1_YChangedSignature OnVertex1_YChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnVertex1_ZChangedSignature OnVertex1_ZChanged;
protected:
	// void CurTimestampChanged(const FOnAttributeChangeData& Data) const;
	// void MaxTimestampChanged(const FOnAttributeChangeData& Data) const;
	// void Vertex1_XChanged(const FOnAttributeChangeData& Data) const;
	// void Vertex1_YChanged(const FOnAttributeChangeData& Data) const;
	// void Vertex1_ZChanged(const FOnAttributeChangeData& Data) const;
};