// Copyright Yizai MathVis

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GeoAttributeSet.h"
#include "SphereAttributeSet.generated.h"



#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class MATHVIS_API USphereAttributeSet : public UGeoAttributeSet
{
	GENERATED_BODY()
public:
	USphereAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&
	OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/*
	 * Primary Attributes
	 */
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_LocationX, Category = "Sphere Attributes")
	FGameplayAttributeData LocationX;
	ATTRIBUTE_ACCESSORS(USphereAttributeSet, LocationX);

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_LocationY, Category = "Sphere Attributes")
	FGameplayAttributeData LocationY;
	ATTRIBUTE_ACCESSORS(USphereAttributeSet, LocationY);

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_LocationZ, Category = "Sphere Attributes")
	FGameplayAttributeData LocationZ;
	ATTRIBUTE_ACCESSORS(USphereAttributeSet, LocationZ);

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_ScaleX, Category = "Sphere Attributes")
	FGameplayAttributeData ScaleX;
	ATTRIBUTE_ACCESSORS(USphereAttributeSet, ScaleX);

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_ScaleY, Category = "Sphere Attributes")
	FGameplayAttributeData ScaleY;
	ATTRIBUTE_ACCESSORS(USphereAttributeSet, ScaleY);

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_ScaleZ, Category = "Sphere Attributes")
	FGameplayAttributeData ScaleZ;
	ATTRIBUTE_ACCESSORS(USphereAttributeSet, ScaleZ);

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Radius, Category = "Sphere Attributes")
	FGameplayAttributeData Radius;
	ATTRIBUTE_ACCESSORS(USphereAttributeSet, Radius);

	/*
	 * Rep Functions
	 */
	UFUNCTION()
	void OnRep_LocationX(const FGameplayAttributeData& OldLocationX) const;

	UFUNCTION()
	void OnRep_LocationY(const FGameplayAttributeData& OldLocationY) const;

	UFUNCTION()
	void OnRep_LocationZ(const FGameplayAttributeData& OldLocationZ) const;

	UFUNCTION()
	void OnRep_ScaleX(const FGameplayAttributeData& OldScaleX) const;

	UFUNCTION()
	void OnRep_ScaleY(const FGameplayAttributeData& OldScaleY) const;

	UFUNCTION()
	void OnRep_ScaleZ(const FGameplayAttributeData& OldScaleZ) const;

	UFUNCTION()
	void OnRep_Radius(const FGameplayAttributeData& OldRadius) const;


};