// Copyright Yizai MathVis

#pragma once

#include "Gate.generated.h"

/**
 * Custom Gate Logic to Use in C++
 */
USTRUCT(BlueprintType)
struct FGate
{
	GENERATED_BODY()

public:
	FGate();
	explicit FGate(bool bStartClosed);

	void Open();
	void Close();
	void Toggle();
	bool IsOpen() const;

private:
	UPROPERTY(VisibleAnywhere)
	bool bGateOpen;
};