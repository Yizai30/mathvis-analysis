// Copyright Yizai MathVis


#include "Actor/Rectangle2DEffectActor.h"

#include "MaterialDomain.h"
#include "MeshDescriptionBuilder.h"
#include "StaticMeshAttributes.h"
#include "PhysicsEngine/BodySetup.h"
#include "Engine/Engine.h"
#include "Materials/Material.h"

ARectangle2DEffectActor::ARectangle2DEffectActor()
{
	Vertices = {
		FVector(0, 0, 0),    // 顶点0
		FVector(0, 0, 100),   // 顶点1
		FVector(0, 100, 100),   // 顶点2
		FVector(0, 100, 0)    // 顶点3
	};

	PreLabels = Labels;
}

void ARectangle2DEffectActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// 创建网格数据
	UStaticMesh* StaticMesh = NewObject<UStaticMesh>(this, TEXT("DynamicTriangleMesh"));
	FMeshDescription MeshDescription;
	FStaticMeshAttributes Attributes(MeshDescription);
	Attributes.Register();

	// 构建网格描述
	FMeshDescriptionBuilder Builder;
	Builder.SetMeshDescription(&MeshDescription);
	Builder.EnablePolyGroups();
	Builder.SetNumUVLayers(1);

	// 添加顶点
	TArray<FVertexID> VertexIDs;
	for (const FVector& Vertex : Vertices)
	{
		VertexIDs.Add(Builder.AppendVertex(Vertex));
	}

	// 添加法线（解决黑面问题，方法是设置法线和顶点到摄像机的连线的夹角小于90度）
	TArray<FVertexInstanceID> VertexInstanceIDs;
	for (FVertexID VertexID : VertexIDs) {
		FVertexInstanceID InstID = Builder.AppendInstance(VertexID);
		Builder.SetInstanceNormal(InstID, FVector(1, 0, 0)); // X轴正向
		VertexInstanceIDs.Add(InstID);
	}

	// 创建多边形（三角形面）
	FPolygonGroupID PolygonGroup = Builder.AppendPolygonGroup();
	Builder.AppendTriangle(VertexInstanceIDs[0], VertexInstanceIDs[1], VertexInstanceIDs[3], PolygonGroup);
	Builder.AppendTriangle(VertexInstanceIDs[1], VertexInstanceIDs[2], VertexInstanceIDs[3], PolygonGroup);

	// 创建静态网格资源
	UStaticMesh::FBuildMeshDescriptionsParams Params;
	Params.bBuildSimpleCollision = true;
	Params.bFastBuild = true;

	TArray<const FMeshDescription*> MeshDescriptions;
	MeshDescriptions.Add(&MeshDescription);

	StaticMesh->BuildFromMeshDescriptions(MeshDescriptions, Params);

	// 配置碰撞
	StaticMesh->CreateBodySetup();
	UBodySetup* BodySetup = StaticMesh->GetBodySetup();
	BodySetup->CollisionTraceFlag = ECollisionTraceFlag::CTF_UseSimpleAsComplex;

	// 应用网格到组件
	GeoMeshComponent->SetStaticMesh(StaticMesh);
	GeoMeshComponent->SetRelativeLocation(FVector::ZeroVector);
}

void ARectangle2DEffectActor::UpdateEdgeLabels()
{
	// Check if GeoMeshComponent has loaded
	if (!GeoMeshComponent)
	{
		return;
	}

	// 当标签发生变更时，更新标签
	if (PreLabels != Labels)
	{
		// 创建 or 更新4个边的标签
		// 1. 获取4个顶点
		TArray<FVector> VertexPositions;
		bool bOutSuccess = false;
		FString OutInfoMessage;
		GetStaticMeshVertexLocations(GeoMeshComponent, VertexPositions, bOutSuccess, OutInfoMessage);
		if (!bOutSuccess)
		{
			UE_LOG(LogTemp, Warning, TEXT("Get Static Mesh Vertex Locations Failed - %s"), *OutInfoMessage);
			return;
		}

		// 2. 依次创建 or 更新标签
		for (int32 i = 0 ; i < Labels.Num(); ++i)
		{
			// 如没有第 i 个标签数据的记录，则创建标签
			if (!EdgeLabelDataArray.IsValidIndex(i))
			{
				CreateEdgeLabel(VertexPositions[(i+2)%3], VertexPositions[i], Labels[i]);
			}
			// 如有第 i 个标签数据的记录，则更新标签
			else
			{
				EdgeLabelDataArray[i].Label = Labels[i];
				UpdateEdgeLabel(EdgeLabelDataArray[i]);
			}
		}

		// 3. 删除多余的标签
		for (int32 i = Labels.Num(); i < EdgeLabelDataArray.Num(); ++i)
		{
			EdgeLabelDataArray[i].TextComponent->DestroyComponent();
		}

		PreLabels = Labels;
	}
}

void ARectangle2DEffectActor::CreateEdgeLabel(const FVector& StartPoint, const FVector& EndPoint,
	const FString& LabelText)
{
	// 转换为本地坐标（相对于RootComponent）
	const FTransform ComponentTransform = RootComponent->GetComponentTransform();
	const FVector LocalStart = ComponentTransform.InverseTransformPosition(StartPoint);
	const FVector LocalEnd = ComponentTransform.InverseTransformPosition(EndPoint);

	// 存储原始数据
	FEdgeLabelData NewData;
	NewData.LocalStart = LocalStart;
	NewData.LocalEnd = LocalEnd;
	NewData.Label = LabelText;

	// 计算边中点和方向
	UE_LOG(LogTemp, Warning, TEXT("StartPoint: %s, EndPoint: %s"), *StartPoint.ToString(), *EndPoint.ToString());
	const FVector MidPoint = (StartPoint + EndPoint) * 0.5f;
	const FVector EdgeDirection = (EndPoint - StartPoint).GetSafeNormal();
	UE_LOG(LogTemp, Warning, TEXT("MidPoint: %s, EdgeDirection: %s"), *MidPoint.ToString(), *EdgeDirection.ToString());

	// 创建文本组件
	UTextRenderComponent* TextComp = NewObject<UTextRenderComponent>(this);
	TextComp->RegisterComponent();
	TextComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// 基础设置
	TextComp->SetText(FText::FromString(LabelText));
	TextComp->SetWorldSize(24.0f); // 字体大小
	TextComp->SetTextRenderColor(FColor{184, 110, 41, 1});
	TextComp->SetHorizontalAlignment(EHTA_Center);
	TextComp->SetVerticalAlignment(EVRTA_TextCenter);

	// 计算标签位置（沿法线偏移）
	const FVector Normal = FVector(0, -EdgeDirection.Z, EdgeDirection.Y); // 2D垂直向量
	UE_LOG(LogTemp, Warning, TEXT("Normal: %s"), *Normal.ToString());
	TextComp->SetWorldLocation(MidPoint - Normal * 20.0f); // 偏移20单位

	// 将文本的旋转方向归零
	TextComp->SetWorldRotation(FRotator(0, 0, 0));

	NewData.TextComponent = TextComp;
	EdgeLabelDataArray.Add(NewData);

	// 初始位置更新
	UpdateEdgeLabel(NewData);
}

void ARectangle2DEffectActor::UpdateEdgeLabel(const FEdgeLabelData& Data) const
{
	if (!Data.TextComponent) return;

	// 获取当前组件变换
	const FTransform ComponentTransform = RootComponent->GetComponentTransform();

	// 转换为世界坐标
	const FVector WorldStart = ComponentTransform.TransformPosition(Data.LocalStart);
	const FVector WorldEnd = ComponentTransform.TransformPosition(Data.LocalEnd);

	// 重新计算位置
	const FVector MidPoint = (WorldStart + WorldEnd) * 0.5f;
	const FVector EdgeDirection = (WorldEnd - WorldStart).GetSafeNormal();

	// 计算法线（优化后的2D垂直计算）
	const FVector Normal = FVector(0, -EdgeDirection.Z, EdgeDirection.Y).GetSafeNormal();

	// 应用新的位置和旋转
	Data.TextComponent->SetWorldLocation(MidPoint - Normal * 20.0f);

	// 更新文本
	Data.TextComponent->SetText(FText::FromString(Data.Label));

	// 将文本的旋转方向归零
	Data.TextComponent->SetWorldRotation(FRotator(0, 0, 0));
}