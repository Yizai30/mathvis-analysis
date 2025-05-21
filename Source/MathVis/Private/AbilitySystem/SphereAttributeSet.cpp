// Copyright Yizai MathVis


#include "AbilitySystem/SphereAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"

USphereAttributeSet::USphereAttributeSet()
{
}

void USphereAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USphereAttributeSet, LocationX, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USphereAttributeSet, LocationY, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USphereAttributeSet, LocationZ, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USphereAttributeSet, ScaleX, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USphereAttributeSet, ScaleY, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USphereAttributeSet, ScaleZ, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USphereAttributeSet, Radius, COND_None, REPNOTIFY_Always);
}

void USphereAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void USphereAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	// TODO: 空间的坐标限制？
}

void USphereAttributeSet::OnRep_LocationX(const FGameplayAttributeData& OldLocationX) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USphereAttributeSet, LocationX, OldLocationX);
}

void USphereAttributeSet::OnRep_LocationY(const FGameplayAttributeData& OldLocationY) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USphereAttributeSet, LocationY, OldLocationY);
}

void USphereAttributeSet::OnRep_LocationZ(const FGameplayAttributeData& OldLocationZ) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USphereAttributeSet, LocationZ, OldLocationZ);
}

void USphereAttributeSet::OnRep_ScaleX(const FGameplayAttributeData& OldScaleX) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USphereAttributeSet, ScaleX, OldScaleX);
}

void USphereAttributeSet::OnRep_ScaleY(const FGameplayAttributeData& OldScaleY) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USphereAttributeSet, ScaleY, OldScaleY);
}

void USphereAttributeSet::OnRep_ScaleZ(const FGameplayAttributeData& OldScaleZ) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USphereAttributeSet, ScaleZ, OldScaleZ);
}

void USphereAttributeSet::OnRep_Radius(const FGameplayAttributeData& OldRadius) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USphereAttributeSet, Radius, OldRadius);
}