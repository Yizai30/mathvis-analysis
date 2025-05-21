// Copyright Yizai MathVis

#pragma once

#include "CoreMinimal.h"
#include "Actor/MVEffectActor.h"
#include "Logic/Gate.h"
#include "TextEffectActor.generated.h"

/**
 * 
 */
UCLASS()
class MATHVIS_API ATextEffectActor : public AMVEffectActor
{
	GENERATED_BODY()
public:
	/** ~~~~~~~~~~~~~~~~~~~~~~~~~ 生命周期 ~~~~~~~~~~~~~~~~~~~~~~~~~ */

	ATextEffectActor();
	virtual void Tick(float DeltaTime) override;

	/**
	 * ~~~~~~~~~~~~~~~~~~~~~~~~~ Other Properties and Functions ~~~~~~~~~~~~~~~~~~~~~~~~~
	 */

	/** Mesh 相关 */
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	// UStaticMeshComponent* TextMeshComponent = nullptr;
	// UFUNCTION(BlueprintCallable)
	// UStaticMeshComponent* GetMesh() const { return TextMeshComponent; }
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInstanceDynamic* TextMeshMaterialInstance;
	// // 跟据鼠标位置设置Actor位置
	// UFUNCTION(BlueprintCallable)
	// virtual void SetTextEffectActorLocation();

	/** Geo Subcomponents' Properties */
	UPROPERTY(VisibleAnywhere, Category="Label")
	FString Content = "S = c^2";
	UFUNCTION(BlueprintCallable, Category="Label")
	virtual void SetContent(const FString& NewContent);

protected:
	FString PreContent = "";
	/** 程序化生成网格 */
	virtual void PostInitializeComponents() override;

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