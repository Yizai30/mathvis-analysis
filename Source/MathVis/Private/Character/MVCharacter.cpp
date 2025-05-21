// Copyright Yizai MathVis


#include "Character/MVCharacter.h"

#include "AbilitySystemComponent.h"
#include "Player/MVPlayerController.h"
#include "Player/MVPlayerState.h"
#include "UI/HUD/MVHUD.h"

AMVCharacter::AMVCharacter()
{
	// GetCharacterMovement()->bOrientRotationToMovement = true;
	// GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	// GetCharacterMovement()->bConstrainToPlane = true;
	// GetCharacterMovement()->bSnapToPlaneAtStart = true;
	//
	// // 角色本身不使用控制器的旋转
	// bUseControllerRotationPitch = false;
	// bUseControllerRotationRoll = false;
	// bUseControllerRotationYaw = false;
}

void AMVCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();
}

void AMVCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void AMVCharacter::InitAbilityActorInfo()
{
	AMVPlayerState* MVPlayerState = GetPlayerState<AMVPlayerState>();
	check(MVPlayerState);
	MVPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo
	(MVPlayerState, this);
	AbilitySystemComponent = MVPlayerState->GetAbilitySystemComponent();
	AttributeSet = MVPlayerState->GetAttributeSet();

	// 考虑多人游戏：只对本地玩家有效，防止空指针错误
	if (AMVPlayerController* MVPlayerController = Cast<AMVPlayerController>
	(GetController()))
	{
		if (AMVHUD* MVHUD = Cast<AMVHUD>(MVPlayerController->GetHUD()))
		{
			MVHUD->InitOverlay(MVPlayerController, MVPlayerState,
			AbilitySystemComponent, AttributeSet);
		}
	}
}