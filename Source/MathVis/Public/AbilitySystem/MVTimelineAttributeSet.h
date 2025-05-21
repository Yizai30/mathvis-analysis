// // Copyright Yizai MathVis
//
// #pragma once
//
// #include "CoreMinimal.h"
// #include "AbilitySystemComponent.h"
// #include "AttributeSet.h"
// #include "MVTimelineAttributeSet.generated.h"
//
// #define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
// GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
// GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
// GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
// GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
//
// /**
//  *
//  */
// UCLASS()
// class MATHVIS_API UMVTimelineAttributeSet : public UAttributeSet
// {
// 	GENERATED_BODY()
// public:
// 	UMVTimelineAttributeSet();
// 	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
//
// 	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CurTimestamp, Category = "Timeline Attributes")
// 	FGameplayAttributeData CurTimestamp;
// 	ATTRIBUTE_ACCESSORS(UMVTimelineAttributeSet, CurTimestamp);
//
// 	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxTimestamp, Category = "Timeline Attributes")
// 	FGameplayAttributeData MaxTimestamp;
// 	ATTRIBUTE_ACCESSORS(UMVTimelineAttributeSet, MaxTimestamp);
//
// 	UFUNCTION()
// 	void OnRep_CurTimestamp(const FGameplayAttributeData& OldCurTimestamp) const;
//
// 	UFUNCTION()
// 	void OnRep_MaxTimestamp(const FGameplayAttributeData& OldMaxTimestamp) const;
// };