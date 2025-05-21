// Copyright Yizai MathVis

#pragma once

#include "CoreMinimal.h"
#include "MVAttributeSet.h"
#include "KeyframeAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class MATHVIS_API UKeyframeAttributeSet : public UMVAttributeSet
{
	GENERATED_BODY()
public:
	UKeyframeAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/**
	 * Vital Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_GeoCount, Category = "Keyframe Vital Attributes")
	FGameplayAttributeData GeoCount;
	ATTRIBUTE_ACCESSORS(UKeyframeAttributeSet, GeoCount);

	/**
	 * Functions
	 */
	UFUNCTION()
	void OnRep_GeoCount(const FGameplayAttributeData& OldGeoCount) const;
};