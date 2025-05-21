// Copyright Yizai MathVis

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SphereAttributeSet.h"
#include "Actor/GeoEffectActor.h"
#include "SphereEffectActor.generated.h"

/**
 * 
 */
UCLASS()
class MATHVIS_API ASphereEffectActor : public AGeoEffectActor
{
	GENERATED_BODY()
public:
	// virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetSphereAttributeSet() const { return SphereAttributeSet; }

	UPROPERTY()
	USphereAttributeSet* SphereAttributeSet; // AttributeSet 实例


};