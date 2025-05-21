// Copyright Yizai MathVis


#include "Player/MVPlayerState.h"

#include "AbilitySystem/GeoAttributeSet.h"
#include "AbilitySystem/MVAbilitySystemComponent.h"
// #include "AbilitySystem/MVAttributeSet.h"

AMVPlayerState::AMVPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMVAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// AttributeSet = CreateDefaultSubobject<UGeoAttributeSet>("AttributeSet");

	SetNetUpdateFrequency(100.f); // 设置频率 将服务端的更新复制到客户端
}

UAbilitySystemComponent* AMVPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}