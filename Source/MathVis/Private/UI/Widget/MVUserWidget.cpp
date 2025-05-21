// Copyright Yizai MathVis


#include "UI/Widget/MVUserWidget.h"

void UMVUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}

AMVEffectActor* UMVUserWidget::SpawnMVEffectActor(TSubclassOf<AMVEffectActor> MVClass, FTransform Transform,
	bool& bOutSuccess, FString& OutInfoMessage)
{
	// Check if MVClass is valid
	if (!MVClass)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Spawn MVEffect Actor Failed - MVClass is null"));
		return nullptr;
	}

	// Check if MVClass is a child of AMVEffectActor
	if (MVClass->IsChildOf(AMVEffectActor::StaticClass()) == false)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Spawn MVEffect Actor Failed - MVClass is not a child of AMVEffectActor"));
		return nullptr;
	}

	// Check if World is valid
	if (GetWorld() == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Spawn MVEffect Actor Failed - World is null"));
		return nullptr;
	}

	AMVEffectActor* MVEffectActor = GetWorld()->SpawnActor<AMVEffectActor>(MVClass, Transform);

	// Check if MVEffectActor is valid
	if (MVEffectActor == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Spawn MVEffect Actor Failed - Was not able to spawn MVEffectActor"));
		return nullptr;
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Spawn MVEffect Actor - '%s' - Succeeded"), *MVClass->GetName());
	return MVEffectActor;
}

AGeoEffectActor* UMVUserWidget::SpawnGeoEffectActor(TSubclassOf<AGeoEffectActor> GeoClass, FTransform Transform,
                                                    bool& bOutSuccess, FString& OutInfoMessage)
{
	// Check if GeoClass is valid
	if (!GeoClass)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Spawn GeoEffect Actor Failed - GeoClass is null"));
		return nullptr;
	}

	// Check if GeoClass is a child of AGeoEffectActor
	if (GeoClass->IsChildOf(AGeoEffectActor::StaticClass()) == false)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Spawn GeoEffect Actor Failed - GeoClass is not a child of AGeoEffectActor"));
		return nullptr;
	}

	// Check if World is valid
	if (GetWorld() == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Spawn GeoEffect Actor Failed - World is null"));
		return nullptr;
	}

	AGeoEffectActor* GeoEffectActor = GetWorld()->SpawnActor<AGeoEffectActor>(GeoClass, Transform);

	// Check if GeoEffectActor is valid
	if (GeoEffectActor == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Spawn GeoEffect Actor Failed - Was not able to spawn GeoEffectActor"));
		return nullptr;
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Spawn GeoEffect Actor - '%s' - Succeeded"), *GeoClass->GetName());
	return GeoEffectActor;
}

ATextEffectActor* UMVUserWidget::SpawnTextEffectActor(TSubclassOf<ATextEffectActor> TextClass, FTransform Transform,
	bool& bOutSuccess, FString& OutInfoMessage) const
{
	// Check if TextClass is valid
	if (!TextClass)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Spawn TextEffect Actor Failed - TextClass is null"));
		return nullptr;
	}

	// Check if World is valid
	if (GetWorld() == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Spawn TextEffect Actor Failed - World is null"));
		return nullptr;
	}

	ATextEffectActor* TextEffectActor = GetWorld()->SpawnActor<ATextEffectActor>(TextClass, Transform);

	// Check if GeoEffectActor is valid
	if (TextEffectActor == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Spawn GeoEffect Actor Failed - Was not able to spawn GeoEffectActor"));
		return nullptr;
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Spawn GeoEffect Actor - '%s' - Succeeded"), *TextClass->GetName());
	return TextEffectActor;
}