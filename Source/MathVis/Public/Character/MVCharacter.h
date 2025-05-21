// Copyright Yizai MathVis

#pragma once

#include "CoreMinimal.h"
#include "Character/MVCharacterBase.h"
#include "MVCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MATHVIS_API AMVCharacter : public AMVCharacterBase
{
	GENERATED_BODY()
public:
	AMVCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
private:
	void InitAbilityActorInfo();
};