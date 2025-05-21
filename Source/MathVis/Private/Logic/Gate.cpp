// Copyright Yizai MathVis


#include "Logic/Gate.h"


FGate::FGate()
{
	bGateOpen = false;
}

FGate::FGate(const bool bStartClosed)
{
	bGateOpen = !bStartClosed;
}

void FGate::Open()
{
	bGateOpen = true;
}

void FGate::Close()
{
	bGateOpen = false;
}

void FGate::Toggle()
{
	bGateOpen = !bGateOpen;
}

bool FGate::IsOpen() const
{
	return bGateOpen;
}