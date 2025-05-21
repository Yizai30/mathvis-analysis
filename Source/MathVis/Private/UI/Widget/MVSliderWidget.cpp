// Copyright Yizai MathVis


#include "UI/Widget/MVSliderWidget.h"

void UMVSliderWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 检查 Slider 控件是否有效
	if (MVSlider) {
		// 绑定 OnValueChanged 事件到 HandleSliderValueChanged 函数
		MVSlider->OnValueChanged.AddDynamic(this, &UMVSliderWidget::HandleSliderValueChanged);
	}
}

void UMVSliderWidget::HandleSliderValueChanged(float Value)
{
	// TODO 依赖 SliderController

	// 在此处编写自定义逻辑
	UE_LOG(LogTemp, Warning, TEXT("Slider Value: %f"), Value);

	// 广播事件到蓝图或其他 C++ 逻辑
	OnMVSliderValueChanged.Broadcast(Value);

	// 如果 Value 大于 0.5f，就在摄像机前方，向前走 200 个向量单位，绘制一个边长为 100 个向量单位的，可以看到的 DebugBox
	if (Value > 0.5f) {
		DrawDebugBox(GetWorld(), GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() + FVector(-200.0f, 0.0f, 100.0f), FVector(80.0f), FColor::Red, true, -1.0f, 0, 2.0f);
	}
}