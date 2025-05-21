// Copyright Yizai MathVis


#include "Actor/Triangle2DEffectActor.h"

#include "MeshDescriptionBuilder.h"
#include "StaticMeshAttributes.h"
#include "StaticMeshOperations.h"
#include "Components/TextRenderComponent.h"
#include "PhysicsEngine/BodySetup.h"
#include "Engine/Engine.h"
#include "Materials/Material.h"

ATriangle2DEffectActor::ATriangle2DEffectActor()
{
	/* Debug: 设置Tick每秒执行1次 */
	// SetActorTickInterval(1.0f);

	// 顶点位置（直角三角形）
	auto V0 = FVector(0, 0, 0);
	auto V1 = FVector(0, 0, 200);
	auto V2 = FVector(0, 100, 0);
	Vertices = {V0, V1, V2};

	// 边标签
	PreLabels = Labels;
}

// 在Tick中持续更新
void ATriangle2DEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateEdgeLabels();

	/**
	 * Debug: 通过GetStaticMeshVertexLocations获取顶点位置，注意修改FrameRate，防止打印太多
	 */
	{
		// TArray<FVector> VertexPositions;
		// bool bOutSuccess = false;
		// FString OutInfoMessage;
		// GetStaticMeshVertexLocations(GeoMeshComponent, VertexPositions, bOutSuccess, OutInfoMessage);
	}
}

void ATriangle2DEffectActor::PostInitializeComponents()
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

	// 在顶点实例设置中添加颜色属性
	// TVertexInstanceAttributesRef<FVector4f> VertexInstanceColors = Attributes.GetVertexInstanceColors();
	// VertexInstanceColors.SetNumChannels(1); // 确保颜色通道开启
	//
	// // 遍历三角形边
	// for (FTriangleID TriangleID : MeshDescription.Triangles().GetElementIDs()) {
	// 	const TArrayView<const FVertexID> TriangleVertices = MeshDescription.GetTriangleVertices(TriangleID);
	//
	// 	// 为每条边设置顶点颜色
	// 	for (int32 i = 0; i < 3; ++i) {
	// 		FVertexID Start = TriangleVertices[i];
	// 		FVertexID End = TriangleVertices[(i+1)%3];
	//
	// 		// 设置边线顶点颜色为红色
	// 		// 安全获取顶点实例
	// 		auto GetValidInstance = [&](FVertexID VertexID) -> FVertexInstanceID {
	// 			const TArray<FVertexInstanceID>& Instances = MeshDescription.GetVertexVertexInstances(VertexID);
	// 			return Instances.Num() > 0 ? Instances[0] : FVertexInstanceID::Invalid;
	// 		};
	//
	// 		if (FVertexInstanceID StartInst = GetValidInstance(Start);
	// 			StartInst != FVertexInstanceID::Invalid)
	// 		{
	// 			VertexInstanceColors.Set(StartInst, 0, FVector4f(1,0,0,1));
	// 		}
	//
	// 		if (FVertexInstanceID EndInst = GetValidInstance(End);
	// 			EndInst != FVertexInstanceID::Invalid)
	// 		{
	// 			VertexInstanceColors.Set(EndInst, 0, FVector4f(1,0,0,1));
	// 		}
	// 	}
	// }

	// 创建多边形（三角形面）
	FPolygonGroupID PolygonGroup = Builder.AppendPolygonGroup();
	Builder.AppendTriangle(VertexInstanceIDs[0], VertexInstanceIDs[1], VertexInstanceIDs[2], PolygonGroup);
	FStaticMeshOperations::ComputeTriangleTangentsAndNormals(MeshDescription);

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

void ATriangle2DEffectActor::UpdateEdgeLabels()
{
	// TODO: 使用一个Map缓存<FrameNum,Label>，使不同帧之间的Label的变换可以被控制

	// Check if GeoMeshComponent has loaded
	if (!GeoMeshComponent)
	{
		return;
	}

	// 当标签发生变更时，更新标签
	if (PreLabels != Labels)
	{
		// 创建 or 更新三个边的标签
		// 1. 获取三个顶点
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

void ATriangle2DEffectActor::CreateEdgeLabel(const FVector& StartPoint, const FVector& EndPoint,
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
	TextComp->SetWorldLocation(MidPoint - Normal * 5.0f + FVector(5, 0, 0)); // 垂直摄像机方向偏移20单位，向摄像机方向偏移5单位

	// 将文本的旋转方向归零
	TextComp->SetWorldRotation(FRotator(0, 0, 0));

	NewData.TextComponent = TextComp;
	EdgeLabelDataArray.Add(NewData);

	// 初始位置更新
	UpdateEdgeLabel(NewData);
}

void ATriangle2DEffectActor::UpdateEdgeLabel(const FEdgeLabelData& Data) const
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
	Data.TextComponent->SetWorldLocation(MidPoint - Normal * 5.0f + FVector(5, 0, 0));

	// 更新文本
	Data.TextComponent->SetText(FText::FromString(Data.Label));

	// 将文本的旋转方向归零
	Data.TextComponent->SetWorldRotation(FRotator(0, 0, 0));
}