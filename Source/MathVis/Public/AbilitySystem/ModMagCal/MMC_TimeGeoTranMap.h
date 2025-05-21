// Copyright Yizai MathVis

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_TimeGeoTranMap.generated.h"

/**
 * 
 */
UCLASS()
class MATHVIS_API UMMC_TimeGeoTranMap : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_TimeGeoTranMap();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

// private:
// 	FGameplayEffectAttributeCaptureDefinition
};