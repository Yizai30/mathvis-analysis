// Copyright Yizai MathVis

#pragma once
#include "Actor/GeoEffectActor.h"

#include "DataStruct.generated.h"

USTRUCT(BlueprintType, Category="Struct|GeoTransform")
struct FGeoTransform
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|GeoTransform")
	AGeoEffectActor* GeoEffectActor = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|GeoTransform")
	FTransform Transform = FTransform::Identity;
};

USTRUCT(BlueprintType, Category="Struct|GeoTransform")
struct FGeoTransformList
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|GeoTransform")
	TArray<FGeoTransform> GeoTransforms = {};
};

USTRUCT(BlueprintType, Category="Struct|TimeTransform")
struct FTimeTransform
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|TimeTransform")
	double FrameNum = 0.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|TimeTransform")
	FTransform Transform = FTransform::Identity;
};

USTRUCT(BlueprintType, Category="Struct|TimeTransform")
struct FTimeTransformList
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|TimeTransform")
	TArray<FTimeTransform> TimeTransforms = {};
};

UCLASS()
class UConstant : public UObject
{
	GENERATED_BODY()
public:
	// UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|Animation Struct")
	// TMap<float, FGeoTransformList> TimeToGeoTransform = {};
	// UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|Animation Struct")
	// TMap<AGeoEffectActor*, FTimeTransformList> GeoToTimeTransform = {};
};