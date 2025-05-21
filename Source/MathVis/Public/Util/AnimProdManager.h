// Copyright Yizai MathVis

#pragma once

#include "CoreMinimal.h"
#include "Actor/GeoEffectActor.h"
#include "Data/DataStruct.h"
#include "AnimProdManager.generated.h"

UCLASS()
class MATHVIS_API UAnimProdManager : public UObject
{
	GENERATED_BODY()

private:
	// double FrameNum = 0.0;
	// TMap<double, FGeoTransformList> TimeToGeoTransforms;
	// TMap<AGeoEffectActor*, FTimeTransformList> GeoEffectActorToTimeTransforms;
	// TArray<AGeoEffectActor*> GeoEffectActors; // 当前选中的 GeoEffectActor
	// TArray<FString> CacheGeos; // 当通过文件导入动画数据时，缓存 GeoEffectActor 的名字
	// TMap<FString, AGeoEffectActor*> GeoNameToActor; // 通过动画数据中唯一的 GeoName 找到对应的 GeoEffectActor
	// GeoNameToClassMap 存储动画数据中的 GeoName 对应到的 GeoEffectActor 的 Class
public:
};