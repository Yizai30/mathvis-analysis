// Copyright Yizai MathVis

#pragma once

#include "CoreMinimal.h"
#include "Actor/GeoEffectActor.h"
#include "Components/TextRenderComponent.h"
#include "Triangle2DEffectActor.generated.h"

/**
 * 
 */
UCLASS()
class MATHVIS_API ATriangle2DEffectActor : public AGeoEffectActor
{
	GENERATED_BODY()

public:
	ATriangle2DEffectActor();

	virtual void Tick(float DeltaTime) override;

protected:

	/** 程序化生成网格 */
	virtual void PostInitializeComponents() override;

	/** 边标签的结构化数据 */
	struct FEdgeLabelData
	{
		FVector LocalStart;    // 本地坐标系起点
		FVector LocalEnd;      // 本地坐标系终点
		FString Label;         // 显示文本
		UTextRenderComponent* TextComponent; // 关联的文本组件
	};
	TArray<FEdgeLabelData> EdgeLabelDataArray; // 边标签列表

	/** 更新所有边标签（在Tick中被调用） */
	void UpdateEdgeLabels();

private:
	/** 创建边标签 */
	void CreateEdgeLabel(const FVector& StartPoint, const FVector& EndPoint, const FString& LabelText);
	/** 更新边标签 */
	void UpdateEdgeLabel(const FEdgeLabelData& Data) const;
};