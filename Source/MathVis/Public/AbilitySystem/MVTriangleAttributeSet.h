// // Copyright Yizai MathVis
//
// #pragma once
//
// #include "CoreMinimal.h"
// #include "AbilitySystemComponent.h"
// #include "AttributeSet.h"
// #include "MVTriangleAttributeSet.generated.h"
//
// #define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
// 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
// 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
// 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
// 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
//
// /**
//  * MVC - Model
//  */
// UCLASS()
// class MATHVIS_API UMVTriangleAttributeSet : public UAttributeSet
// {
// 	GENERATED_BODY()
// public:
// 	UMVTriangleAttributeSet();
// 	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&
// 	OutLifetimeProps) const override;
//
// 	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vertex1_X, Category = "Triangle Attributes")
// 	FGameplayAttributeData Vertex1_X;
// 	ATTRIBUTE_ACCESSORS(UMVTriangleAttributeSet, Vertex1_X);
//
// 	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vertex1_Y, Category = "Triangle Attributes")
// 	FGameplayAttributeData Vertex1_Y;
// 	ATTRIBUTE_ACCESSORS(UMVTriangleAttributeSet, Vertex1_Y);
//
// 	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vertex1_Z, Category = "Triangle Attributes")
// 	FGameplayAttributeData Vertex1_Z;
// 	ATTRIBUTE_ACCESSORS(UMVTriangleAttributeSet, Vertex1_Z);
//
// 	UFUNCTION()
// 	void OnRep_Vertex1_X(const FGameplayAttributeData& OldVertex1_X) const;
//
// 	UFUNCTION()
// 	void OnRep_Vertex1_Y(const FGameplayAttributeData& OldVertex1_Y) const;
//
// 	UFUNCTION()
// 	void OnRep_Vertex1_Z(const FGameplayAttributeData& OldVertex1_Z) const;
// };