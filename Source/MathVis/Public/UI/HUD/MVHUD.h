// Copyright Yizai MathVis

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MVHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UMVUserWidget;
/**
 * 
 */
UCLASS()
class MATHVIS_API AMVHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<UMVUserWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const
	FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS,
	UAbilitySystemComponent* ASC, UAttributeSet* AS);
protected:

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMVUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};