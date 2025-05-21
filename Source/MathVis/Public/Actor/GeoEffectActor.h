// Copyright Yizai MathVis

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "MVEffectActor.h"
#include "AbilitySystem/GeoAttributeSet.h"
#include "Logic/Gate.h"
#include "GeoEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class ESphereEffectApplicationPolicy : uint8
{
	ApplyOnClicked,
	ApplyOnEndClicked,
	DoNotApply
};

UENUM(BlueprintType)
enum class ESphereEffectRemovalPolicy : uint8
{
	RemoveOnEndClicked,
	DoNotRemove
};

UCLASS()
class MATHVIS_API AGeoEffectActor : public AMVEffectActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	/** ~~~~~~~~~~~~~~~~~~~~~~~~~ 生命周期 ~~~~~~~~~~~~~~~~~~~~~~~~~ */

	AGeoEffectActor();
	virtual void Tick(float DeltaTime) override;

	/**
	 * ~~~~~~~~~~~~~~~~~~~~~~~~~ Gameplay Ability System ~~~~~~~~~~~~~~~~~~~~~~~~~
	 */

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetGeoAttributeSet() const { return GeoAttributeSet; }
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY()
	UGeoAttributeSet* GeoAttributeSet;

	/**
	 * ~~~~~~~~~~~~~~~~~~~~~~~~~ Other Properties and Functions ~~~~~~~~~~~~~~~~~~~~~~~~~
	 */

	/** Mesh 相关 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* GeoMeshComponent = nullptr;
	UFUNCTION(BlueprintCallable)
	UStaticMeshComponent* GetMesh() const { return GeoMeshComponent; }
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInstanceDynamic* GeoMeshMaterialInstance;
	/** Events */
	virtual void NotifyActorOnReleased(FKey ButtonReleased = EKeys::LeftMouseButton) override;
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;
	/** Effects */
	UFUNCTION(BlueprintCallable)
	virtual void HighlightActor();
	UFUNCTION(BlueprintCallable)
	virtual void UnHighlightActor();
	// 跟据鼠标位置设置Actor位置
	UFUNCTION(BlueprintCallable)
	virtual void SetGeoEffectActorLocation();
	/** Utilities */
	/**
	 * Get the vertex positions of a static mesh component
	 *
	 * @param StaticMeshComponent the static mesh component to get vertex positions from
	 * @param VertexPositions the array to store vertex positions in
	 * @param bOutSuccess if the action was a success or not
	 * @param OutInfoMessage more information about the action's result
	 *
	 * @return
	 */
	UFUNCTION(BlueprintCallable)
	void GetStaticMeshVertexLocations(UStaticMeshComponent* StaticMeshComponent, TArray<FVector>& VertexPositions,
	                                  bool& bOutSuccess, FString& OutInfoMessage) const;
	/** Geo Subcomponents' Properties */
	UPROPERTY(VisibleAnywhere, Category="Label")
	TArray<FString> Labels = {};
	UFUNCTION(BlueprintCallable, Category="Label")
	virtual void SetLabels(const TArray<FString>& NewLabels);


protected:
	/** ~~~~~~~~~~~~~~~~~~~~~~~~~ 生命周期 ~~~~~~~~~~~~~~~~~~~~~~~~~ */
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * ~~~~~~~~~~~~~~~~~~~~~~~~~ Gameplay Ability System ~~~~~~~~~~~~~~~~~~~~~~~~~
	 */
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnFocus(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndFocus(AActor* TargetActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	bool bDestroyOnEffectRemoval = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	ESphereEffectApplicationPolicy InstantEffectApplicationPolicy = ESphereEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	ESphereEffectApplicationPolicy DurationEffectApplicationPolicy = ESphereEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	ESphereEffectApplicationPolicy InfiniteEffectApplicationPolicy = ESphereEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	ESphereEffectRemovalPolicy InfiniteEffectRemovalPolicy = ESphereEffectRemovalPolicy::RemoveOnEndClicked;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	float ActorLevel = 1.f;

protected:
	/** vertices of the shape */
	TArray<FVector> Vertices;
	/** 检查标签是否改变 */
	TArray<FString> PreLabels;

private:
	/** 使用自定义的 Gate 逻辑，
	 * 实现按下鼠标左键拖拽，释放鼠标左键停止拖拽并影响Actor被选中/未被选中。
	 *
	 * 1. Tick连接Gate的Enter
	 * 2. OnClick连接Gate的Open
	 * 3. OnReleased连接Gate的Close
	 * 4. Gate默认StartClosed为true
	 * 5. Gate的Exit连接SetActorLocation函数
	 */
	FGate Gate = FGate(true);

	/** be used to calculate the world position of the effect actor */
	double HitDistance;
	FVector HitLocation;
	FVector HitActorLocation;
};