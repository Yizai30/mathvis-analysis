// Copyright Yizai MathVis


#include "Actor/TextEffectActor.h"

#include "Components/TextRenderComponent.h"

ATextEffectActor::ATextEffectActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// TextMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TextMeshComponent"));
	// TextMeshComponent->SetupAttachment(RootComponent); // 附加到根组件
}

void ATextEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATextEffectActor::SetContent(const FString& NewContent)
{
	Content = NewContent;
}

void ATextEffectActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// 创建文本组件
	UTextRenderComponent* TextComp = NewObject<UTextRenderComponent>(this);
	TextComp->RegisterComponent();
	TextComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// 基础设置
	TextComp->SetText(FText::FromString(Content));
	TextComp->SetWorldSize(32.0f); // 字体大小
	TextComp->SetTextRenderColor(FColor{137, 134, 5, 1});
	TextComp->SetHorizontalAlignment(EHTA_Center);
	TextComp->SetVerticalAlignment(EVRTA_TextCenter);

	// 将文本的旋转方向归零
	TextComp->SetWorldRotation(FRotator(0, 0, 0));
}