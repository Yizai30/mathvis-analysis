// Copyright Yizai MathVis

#pragma once

#include "CoreMinimal.h"
#include "Components/Slider.h"
#include "UI/Widget/MVUserWidget.h"
#include "MVSliderWidget.generated.h"

/**
 * 
 */
UCLASS()
class MATHVIS_API UMVSliderWidget : public UMVUserWidget
{
	GENERATED_BODY()
public:
	// 绑定到蓝图中的 Slider 控件
	UPROPERTY(meta = (BindWidget)) // 必须与蓝图中的变量名一致
	USlider* MVSlider;

	// 动态委托声明（必须在 UCLASS 宏下方）
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSliderValueChanged, float, Value);

	// 公开给蓝图的事件
	UPROPERTY(BlueprintAssignable, Category = "Slider")
	FOnSliderValueChanged OnMVSliderValueChanged;

	// 初始化事件绑定
	virtual void NativeConstruct() override;

private:
	// Slider 值变化时的 C++ 回调函数
	UFUNCTION()
	void HandleSliderValueChanged(float Value);

protected:
	UPROPERTY()
	TObjectPtr<AActor> SpawnedCube; // 保存生成的立方体引用

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	UMaterialInterface* RedMaterial; // 通过编辑器指定红色材质

};