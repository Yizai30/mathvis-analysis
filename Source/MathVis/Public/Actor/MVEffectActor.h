// Copyright Yizai MathVis

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MVEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UCLASS()
class MATHVIS_API AMVEffectActor : public AActor
{
	GENERATED_BODY()
	
public:
	AMVEffectActor();

protected:
	virtual void BeginPlay() override;
};