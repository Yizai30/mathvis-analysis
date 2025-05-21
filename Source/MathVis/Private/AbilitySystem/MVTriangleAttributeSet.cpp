// // Copyright Yizai MathVis
//
//
// #include "AbilitySystem/MVTriangleAttributeSet.h"
//
// #include "Net/UnrealNetwork.h"
//
// UMVTriangleAttributeSet::UMVTriangleAttributeSet()
// {
// 	InitVertex1_X(0.0f);
// 	InitVertex1_Y(0.0f);
// 	InitVertex1_Z(0.0f);
// }
//
// void UMVTriangleAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
// {
// 	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
// 	DOREPLIFETIME_CONDITION_NOTIFY(UMVTriangleAttributeSet, Vertex1_X, COND_None,
// 	REPNOTIFY_Always);
// 	DOREPLIFETIME_CONDITION_NOTIFY(UMVTriangleAttributeSet, Vertex1_Y, COND_None,
// 	REPNOTIFY_Always);
// 	DOREPLIFETIME_CONDITION_NOTIFY(UMVTriangleAttributeSet, Vertex1_Z, COND_None,
// 	REPNOTIFY_Always);
// }
//
// void UMVTriangleAttributeSet::OnRep_Vertex1_X(const FGameplayAttributeData& OldVertex1_X) const
// {
// 	GAMEPLAYATTRIBUTE_REPNOTIFY(UMVTriangleAttributeSet, Vertex1_X, OldVertex1_X);
// }
//
// void UMVTriangleAttributeSet::OnRep_Vertex1_Y(const FGameplayAttributeData& OldVertex1_Y) const
// {
// 	GAMEPLAYATTRIBUTE_REPNOTIFY(UMVTriangleAttributeSet, Vertex1_Y, OldVertex1_Y);
// }
//
// void UMVTriangleAttributeSet::OnRep_Vertex1_Z(const FGameplayAttributeData& OldVertex1_Z) const
// {
// 	GAMEPLAYATTRIBUTE_REPNOTIFY(UMVTriangleAttributeSet, Vertex1_Z, OldVertex1_Z);
// }