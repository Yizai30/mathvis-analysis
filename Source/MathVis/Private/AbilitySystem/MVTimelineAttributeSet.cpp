// // Copyright Yizai MathVis
//
//
// #include "AbilitySystem/MVTimelineAttributeSet.h"
//
// #include "Net/UnrealNetwork.h"
//
// UMVTimelineAttributeSet::UMVTimelineAttributeSet()
// {
// 	InitCurTimestamp(0.0f);
// 	InitMaxTimestamp(60.0f);
// }
//
// void UMVTimelineAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
// {
// 	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
// 	DOREPLIFETIME_CONDITION_NOTIFY(UMVTimelineAttributeSet, CurTimestamp, COND_None,
// 	REPNOTIFY_Always);
// 	DOREPLIFETIME_CONDITION_NOTIFY(UMVTimelineAttributeSet, MaxTimestamp, COND_None,
// 	REPNOTIFY_Always);
// }
//
// void UMVTimelineAttributeSet::OnRep_CurTimestamp(const FGameplayAttributeData& OldCurTimestamp) const
// {
// 	GAMEPLAYATTRIBUTE_REPNOTIFY(UMVTimelineAttributeSet, CurTimestamp, OldCurTimestamp);
// }
//
// void UMVTimelineAttributeSet::OnRep_MaxTimestamp(const FGameplayAttributeData& OldMaxTimestamp) const
// {
// 	GAMEPLAYATTRIBUTE_REPNOTIFY(UMVTimelineAttributeSet, MaxTimestamp, OldMaxTimestamp);
// }