// Copyright Yizai MathVis


#include "AbilitySystem/KeyframeAttributeSet.h"

#include "Net/UnrealNetwork.h"

UKeyframeAttributeSet::UKeyframeAttributeSet()
{
}

void UKeyframeAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UKeyframeAttributeSet, GeoCount, COND_None, REPNOTIFY_Always);
}

void UKeyframeAttributeSet::OnRep_GeoCount(const FGameplayAttributeData& OldGeoCount) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UKeyframeAttributeSet, GeoCount, OldGeoCount);
}