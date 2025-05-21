// Copyright Yizai MathVis


#include "Actor/GeoEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameInstance/MVGameInstanceAnimProdSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "MathVis/MathVis.h"
#include "PhysicsEngine/BodySetup.h"

// Sets default values
AGeoEffectActor::AGeoEffectActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 创建 AbilitySystemComponent
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	// 创建 AttributeSet 实例
	GeoAttributeSet = CreateDefaultSubobject<UGeoAttributeSet>(TEXT("GeoAttributeSet"));

	// 注册 AttributeSet 到 ASC
	if (AbilitySystemComponent && GeoAttributeSet)
	{
		// 关键步骤：将 AttributeSet 添加到 ASC 的 SparseAttributeSet 列表中
		AbilitySystemComponent->AddAttributeSetSubobject(GeoAttributeSet);
	}

	GeoMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GeoMeshComponent"));
	GeoMeshComponent->SetupAttachment(RootComponent); // 附加到根组件

	// 加载 GeoEffectActor 的默认材质 MI_BasicGeo
	// UMaterial* GeoMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/Assets/Materials/Geometry/MI_BasicGeo.MI_BasicGeo")).Get();
	// GeoMaterial->TwoSided = true; // 临时调试用
	// GeoMaterial->SetShadingModel(MSM_Unlit); // 或确认光照模型正确
	// GeoMeshMaterialInstance = UMaterialInstanceDynamic::Create(GeoMaterial, GeoMeshComponent);
	// GeoMeshComponent->SetMaterial(0, GeoMeshMaterialInstance);
}

UAbilitySystemComponent* AGeoEffectActor::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AGeoEffectActor::BeginPlay()
{
	Super::BeginPlay();

	// 鼠标初始设置：显示光标、启用点击事件
	const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	EnableInput(PlayerController);
	PlayerController->bShowMouseCursor = true;
	PlayerController->bEnableClickEvents = true;
}

void AGeoEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel,
		EffectContextHandle);
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(
		*EffectSpecHandle.Data.Get
		());

	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy ==
		EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteEffectRemovalPolicy == ESphereEffectRemovalPolicy::RemoveOnEndClicked)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}
}

void AGeoEffectActor::OnFocus(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == ESphereEffectApplicationPolicy::ApplyOnClicked)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == ESphereEffectApplicationPolicy::ApplyOnClicked)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == ESphereEffectApplicationPolicy::ApplyOnClicked)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AGeoEffectActor::OnEndFocus(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == ESphereEffectApplicationPolicy::ApplyOnEndClicked)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == ESphereEffectApplicationPolicy::ApplyOnEndClicked)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == ESphereEffectApplicationPolicy::ApplyOnEndClicked)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if (InfiniteEffectRemovalPolicy == ESphereEffectRemovalPolicy::RemoveOnEndClicked)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		for (auto& Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}

void AGeoEffectActor::NotifyActorOnReleased(const FKey ButtonReleased)
{
	Super::NotifyActorOnReleased(ButtonReleased);

	// 选中 = 高亮；取消选中 = 取消高亮
	if (UMVGameInstanceAnimProdSubsystem* GIAnimProdSubsystem = GetGameInstance()->GetSubsystem<
			UMVGameInstanceAnimProdSubsystem>();
		GIAnimProdSubsystem->GeoEffectActors.Find(this) == INDEX_NONE)
	{
		GIAnimProdSubsystem->GeoEffectActors.Add(this);
		HighlightActor();
	}
	else
	{
		GIAnimProdSubsystem->GeoEffectActors.Remove(this);
		UnHighlightActor();
	}

	// TODO: 选中 = 显示属性修改面板；取消选中 = 隐藏属性修改面板

	// enable input
	const auto PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerPawn->EnableInput(PlayerController);

	Gate.Close();
}

void AGeoEffectActor::NotifyActorOnClicked(const FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	FHitResult HitResult;
	// init actor location related variables
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(
		UEngineTypes::ConvertToTraceType(ECC_Visibility), true, HitResult);
	HitDistance = HitResult.Distance;
	HitLocation = HitResult.Location;
	HitActorLocation = HitResult.GetActor()->GetActorLocation();

	// disable input
	const auto PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerPawn->DisableInput(PlayerController);

	Gate.Open();
}

void AGeoEffectActor::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AGeoEffectActor::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
}

void AGeoEffectActor::SetGeoEffectActorLocation()
{
	const auto PlayerController = GetWorld()->GetFirstPlayerController();
	float MouseLocationX, MouseLocationY;
	PlayerController->GetMousePosition(MouseLocationX, MouseLocationY);
	const auto ScreenPosition = FVector2D(MouseLocationX, MouseLocationY);
	FVector WorldPosition, WorldDirection;
	UGameplayStatics::DeprojectScreenToWorld(PlayerController, ScreenPosition, WorldPosition, WorldDirection);
	const FVector NewActorLocation = HitDistance * WorldDirection + WorldPosition - HitLocation + HitActorLocation;
	SetActorLocation(NewActorLocation);
}

// Called every frame
void AGeoEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Gate.IsOpen())
	{
		SetGeoEffectActorLocation();
	}
}

void AGeoEffectActor::SetLabels(const TArray<FString>& NewLabels)
{
	Labels = NewLabels;
}

void AGeoEffectActor::GetStaticMeshVertexLocations(UStaticMeshComponent* StaticMeshComponent,
                                                   TArray<FVector>& VertexPositions, bool& bOutSuccess,
                                                   FString& OutInfoMessage) const
{
	// Check to see if the object appears to be valid
	if (!IsValidLowLevel())
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Get Static Mesh Vertex Locations Failed - Actor is null"));
		return;
	}

	// Check if StaticMeshComponent is valid
	if (!StaticMeshComponent)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Get Static Mesh Vertex Locations Failed - StaticMeshComponent is null"));
		return;
	}

	// Check if StaticMeshComponent has a StaticMesh
	if (!StaticMeshComponent->GetStaticMesh())
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Get Static Mesh Vertex Locations Failed - StaticMeshComponent->GetStaticMesh() is null"));
		return;
	}

	// Check if StaticMeshComponent has a StaticMesh->RenderData
	if (!StaticMeshComponent->GetStaticMesh()->GetRenderData())
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT(
			"Get Static Mesh Vertex Locations Failed - StaticMeshComponent->GetStaticMesh()->GetRenderData() is null"));
		return;
	}

	// Get VertexPositions from VertexBuffer
	if (StaticMeshComponent->GetStaticMesh()->GetRenderData()->LODResources.Num() > 0)
	{
		if (FPositionVertexBuffer* VertexBuffer = &StaticMeshComponent->GetStaticMesh()->GetRenderData()->LODResources[
			0].VertexBuffers.PositionVertexBuffer)
		{
			const int32 VertexCount = VertexBuffer->GetNumVertices();
			for (int32 Index = 0; Index < VertexCount; Index++)
			{
				//This is in the Static Mesh Actor Class, so it is location and tranform of the SMActor
				const FVector WorldSpaceVertexLocation = GetActorLocation() + GetTransform().TransformVector(
					FVector(VertexBuffer->VertexPosition(Index)));
				//add to output FVector array
				VertexPositions.Add(WorldSpaceVertexLocation);
			}
		}
	}

	/** Debug: make VertexPositions to FString */
	// auto VertexPositionsStr = "[" + FString(std::to_string(VertexPositions.Num()).c_str()) + "] - ";
	// for (int32 i = 0; i < VertexPositions.Num(); i++)
	// {
	// 	auto Element = VertexPositions[i];
	// 	VertexPositionsStr += "(" + FString(std::to_string(i).c_str()) + ")" + Element.ToString() + ";";
	// }

	bOutSuccess = true;

	/** Debug: log Vetices' Position, should take care of the Tick rate */
	// OutInfoMessage = FString::Printf(TEXT("Get Static Mesh Vertex Locations - Succeeded"));
	// OutInfoMessage = FString::Printf(TEXT("Get Static Mesh - %s - Vertex Locations - %s - Succeeded"), *GetName(), *VertexPositionsStr);
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *OutInfoMessage);
}