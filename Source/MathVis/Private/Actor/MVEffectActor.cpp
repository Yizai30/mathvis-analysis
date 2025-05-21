// Copyright Yizai MathVis


#include "Actor/MVEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

// Sets default values
AMVEffectActor::AMVEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AMVEffectActor::BeginPlay()
{
	Super::BeginPlay();
}