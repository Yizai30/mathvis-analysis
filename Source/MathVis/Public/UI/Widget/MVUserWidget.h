// Copyright Yizai MathVis

#pragma once

#include "CoreMinimal.h"
#include "Actor/GeoEffectActor.h"
#include "Actor/TextEffectActor.h"
#include "Blueprint/UserWidget.h"
#include "MVUserWidget.generated.h"

/**
 * MVC - View
 */
UCLASS()
class MATHVIS_API UMVUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	/**
	 * Spawn a MVEffectActor
	 *
	 * @param MVClass MVEffectActor 的 Class
	 * @param Transform MVEffectActor 的初始 Transform
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More Information about the action's result
	 *
	 * @return GeoEffectActor*
	 */
	UFUNCTION(BlueprintCallable, Category="AnimProdManager|Spawn Actor")
	AMVEffectActor* SpawnMVEffectActor(TSubclassOf<AMVEffectActor> MVClass, FTransform Transform, bool& bOutSuccess, FString& OutInfoMessage);

	/**
	 * Spawn a GeoEffectActor
	 *
	 * @param GeoClass GeoEffectActor 的 Class
	 * @param Transform GeoEffectActor 的初始 Transform
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More Information about the action's result
	 *
	 * @return GeoEffectActor*
	 */
	UFUNCTION(BlueprintCallable, Category="AnimProdManager|Spawn Actor")
	AGeoEffectActor* SpawnGeoEffectActor(TSubclassOf<AGeoEffectActor> GeoClass, FTransform Transform, bool& bOutSuccess, FString& OutInfoMessage);

	/**
	 * Spawn a TextEffectActor
	 *
	 * @param TextClass TextEffectActor 的 Class
	 * @param Transform GeoEffectActor 的初始 Transform
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More Information about the action's result
	 *
	 * @return ATextEffectActor*
	 */
	UFUNCTION(BlueprintCallable, Category="AnimProdManager|Spawn Actor")
	ATextEffectActor* SpawnTextEffectActor(TSubclassOf<ATextEffectActor> TextClass, FTransform Transform, bool& bOutSuccess, FString& OutInfoMessage) const;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};