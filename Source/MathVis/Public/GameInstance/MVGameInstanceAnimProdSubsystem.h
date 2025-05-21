// Copyright Yizai MathVis

#pragma once

#include "CoreMinimal.h"
#include "Actor/GeoEffectActor.h"
#include "Data/DataStruct.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MVGameInstanceAnimProdSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MATHVIS_API UMVGameInstanceAnimProdSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimProd")
	double FrameNum = 0.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimProd")
	TMap<double, FGeoTransformList> TimeToGeoTransforms;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimProd")
	TMap<AGeoEffectActor*, FTimeTransformList> GeoEffectActorToTimeTransforms;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimProd")
	TArray<AGeoEffectActor*> GeoEffectActors; // 当前选中的 GeoEffectActor
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimProd")
	TArray<FString> CacheGeos; // 当通过文件导入动画数据时，缓存 GeoEffectActor 的名字
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AnimProd")
	TMap<FString, AGeoEffectActor*> GeoNameToActor; // 通过动画数据中唯一的 GeoName 找到对应的 GeoEffectActor
	// GeoNameToClassMap 存储动画数据中的 GeoName 对应到的 GeoEffectActor 的 Class
};