// Copyright Yizai MathVis


#include "AbilitySystem/ModMagCal/MMC_TimeGeoTranMap.h"

UMMC_TimeGeoTranMap::UMMC_TimeGeoTranMap()
{
}

float UMMC_TimeGeoTranMap::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	return Super::CalculateBaseMagnitude_Implementation(Spec);
	// // Gather tags from source and target
	// const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	// const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	//
	// FAggregatorEvaluateParameters EvaluationParameters;
	// EvaluationParameters.SourceTags = SourceTags;
	// EvaluationParameters.TargetTags = TargetTags;
	//
	// float Vigor = 0.f;
	// GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluationParameters, Vigor);
	// Vigor = FMath::Max<float>(Vigor, 0.f);
	//
	// ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	// const int32 PlayerLevel = CombatInterface->GetPlayerLevel();
	//
	// return 80.f + 2.5f * Vigor + 10.f * PlayerLevel;
}