// Copyright Yizai MathVis


#include "AbilitySystem/MVAbilitySystemBPFLibrary.h"

#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "SequencerTools.h"
#include "MovieScene.h"
#include "MovieSceneSection.h"
#include "Misc/FrameRate.h"
#include "Tracks/MovieSceneCameraCutTrack.h"
#include "Tracks/MovieScene3DTransformTrack.h"
#include "Sections/MovieSceneCameraCutSection.h"
#include "Sections/MovieScene3DTransformSection.h"
#include "Camera/CameraActor.h"
#include "Channels/MovieSceneChannelProxy.h"
#include "Channels/MovieSceneDoubleChannel.h"
#include "AutomatedLevelSequenceCapture.h"
#include "Protocols/ImageSequenceProtocol.h"
#include "Protocols/VideoCaptureProtocol.h"
#include "Protocols/AudioCaptureProtocol.h"

ASphereEffectActor* UMVAbilitySystemBPFLibrary::CreateSphereEffectActor(UObject* WorldContextObject,
	FTransform Transform, bool& bOutSuccess, FString& OutInfoMessage)
{
	// get world object
	UWorld* World = WorldContextObject->GetWorld();
	if (!World)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Create Sphere Effect Actor Failed - World isn't valid."));
		return nullptr;
	}

	// spawn actor
	const ASphereEffectActor* SphereEffectActor = World->SpawnActor<ASphereEffectActor>(
		ASphereEffectActor::StaticClass(),
		Transform);
	if (!SphereEffectActor)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Create Sphere Effect Actor Failed - Sphere Effect Actor isn't valid."));
		return nullptr;
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Create Sphere Effect Actor Succeeded."));
	return const_cast<ASphereEffectActor*>(SphereEffectActor);
}

FGuid UMVAbilitySystemBPFLibrary::GetActorGuidFromLevelSequence(AActor* Actor, FString LevelSequencePath,
                                                                bool& bOutSuccess, FString& OutInfoMessage)
{
	// Validate Actor
	if (Actor == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Get Actor Guid From Level Sequence Failed - Actor isn't valid. '%s'"),
		                                 *LevelSequencePath);
		return FGuid();
	}

	// Load Level Sequence
	ULevelSequence* LevelSequence = Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr,
	                                                                      *LevelSequencePath));

	if (LevelSequence == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Get Actor Guid From Level Sequence Failed - Level Sequence isn't valid. '%s'"), *LevelSequencePath);
		return FGuid();
	}

	// Get Actor Guid from Level Sequence
	const FGuid Guid = LevelSequence->FindBindingFromObject(Actor, Actor->GetWorld());

	bOutSuccess = Guid.IsValid();
	const FString SucceededOrFailed = bOutSuccess ? "Succeeded" : "Failed";
	OutInfoMessage = FString::Printf(
		TEXT("Get Actor Guid From Level Sequence %s - %s"), *SucceededOrFailed, *LevelSequencePath);
	return Guid;
}

FGuid UMVAbilitySystemBPFLibrary::AddActorIntoLevelSequence(AActor* Actor, FString LevelSequencePath,
                                                              bool& bOutSuccess, FString& OutInfoMessage)
{
	// Get Actor Guid
	FGuid Guid = GetActorGuidFromLevelSequence(Actor, LevelSequencePath, bOutSuccess, OutInfoMessage);

	if (Guid.IsValid())
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Add Actor Into Level Sequence Failed - Actor is already in the level sequence. '%s'"),
			*LevelSequencePath);
		return Guid;
	}

	// Validate Actor
	if (Actor == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Add Actor Into Level Sequence Failed - Actor isn't valid. '%s'"), *LevelSequencePath);
		return FGuid();
	}

	// Load Level Sequence
	ULevelSequence* LevelSequence = Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr,
	                                                                      *LevelSequencePath));

	if (LevelSequence == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Add Actor Into Level Sequence Failed - Level Sequence isn't valid. '%s'"), *LevelSequencePath);
		return FGuid();
	}

	// Create Actor Track into Level Sequence and link it with the Actor
	Guid = Cast<UMovieSceneSequence>(LevelSequence)->CreatePossessable(Actor);

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Add Actor Into Level Sequence Succeeded - %s"), *LevelSequencePath);
	return Guid;
}

void UMVAbilitySystemBPFLibrary::RemoveActorFromLevelSequence(AActor* Actor, FString LevelSequencePath,
                                                                bool& bOutSuccess, FString& OutInfoMessage)
{
	// Get Actor Guid
	FGuid Guid = GetActorGuidFromLevelSequence(Actor, LevelSequencePath, bOutSuccess, OutInfoMessage);

	if (!Guid.IsValid())
	{
		return;
	}

	// Load Level Sequence
	ULevelSequence* LevelSequence = Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr,
	                                                                      *LevelSequencePath));

	// Unbind Track from Actor
	LevelSequence->UnbindPossessableObjects(Guid);

	// Remove Actor Track from Level Sequence
	bOutSuccess = LevelSequence->MovieScene->RemovePossessable(Guid);

	FString SucceededOrFailed = bOutSuccess ? "Succeeded" : "Failed";
	OutInfoMessage = FString::Printf(
		TEXT("Remove Actor From Level Sequence %s - %s"), *SucceededOrFailed, *LevelSequencePath);
}

UMovieSceneCameraCutTrack* UMVAbilitySystemBPFLibrary::GetCameraCutTrackFromLevelSequence(FString LevelSequencePath,
	bool& bOutSuccess, FString& OutInfoMessage)
{
	// Load level sequence
	ULevelSequence* LevelSequence = Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr,
																		  *LevelSequencePath));

	if (LevelSequence == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Get Camera Cut Track From Level Sequence Failed - Level Sequence isn't valid. '%s'"),
										 *LevelSequencePath);
		return nullptr;
	}

	// Get the camera cut track
	UMovieSceneCameraCutTrack* CameraCutTrack = Cast<UMovieSceneCameraCutTrack>(LevelSequence->MovieScene->GetCameraCutTrack());

	bOutSuccess = CameraCutTrack != nullptr;
	const FString SucceededOrFailed = bOutSuccess ? "Succeeded" : "Failed";
	OutInfoMessage = FString::Printf(
		TEXT("Get Camera Cut Track From Level Sequence %s - %s"), *SucceededOrFailed, *LevelSequencePath);
	return CameraCutTrack;
}

UMovieSceneCameraCutTrack* UMVAbilitySystemBPFLibrary::AddCameraCutTrackInLevelSequence(FString LevelSequencePath,
	bool& bOutSuccess, FString& OutInfoMessage)
{
	// Check if there's a camera cut track in the level sequence
	UMovieSceneCameraCutTrack* CameraCutTrack = GetCameraCutTrackFromLevelSequence(LevelSequencePath, bOutSuccess,
																				  OutInfoMessage);

	if (CameraCutTrack != nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Add Camera Cut Track In Level Sequence Failed - Track already in level sequence. '%s'"),
			*LevelSequencePath);
		return CameraCutTrack;
	}

	// Load level sequence
	ULevelSequence* LevelSequence = Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr,
																		  *LevelSequencePath));
	if (LevelSequence == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Add Camera Cut Track In Level Sequence Failed - Level Sequence isn't valid. '%s'"),
										 *LevelSequencePath);
		return nullptr;
	}

	// Add track
	CameraCutTrack = Cast<UMovieSceneCameraCutTrack>(LevelSequence->MovieScene->AddCameraCutTrack(UMovieSceneCameraCutTrack::StaticClass()));

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(
		TEXT("Add Camera Cut Track In Level Sequence Succeeded - %s"), *LevelSequencePath);
	return CameraCutTrack;
}

void UMVAbilitySystemBPFLibrary::RemoveCameraCutTrackFromLevelSequence(
	FString LevelSequencePath, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Check if there's a camera cut track in the level sequence
	UMovieSceneCameraCutTrack* CameraCutTrack = GetCameraCutTrackFromLevelSequence(LevelSequencePath, bOutSuccess,
																				  OutInfoMessage);
	if (CameraCutTrack == nullptr)
	{
		return;
	}

	// Load level sequence
	ULevelSequence* LevelSequence = Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr,
																		  *LevelSequencePath));
	// Remove track
	LevelSequence->MovieScene->RemoveCameraCutTrack();

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(
		TEXT("Remove Camera Cut Track From Level Sequence Succeeded - %s"), *LevelSequencePath);
}

void UMVAbilitySystemBPFLibrary::LinkCameraToCameraCutTrack(FString LevelSequencePath, ACameraActor* CameraActor,
	int StartFrame, int EndFrame, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Make sure camera is valid
	if (CameraActor == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Link Camera To Camera Cut Track Failed - Camera actor isn't valid. '%s'"), *LevelSequencePath);
		return;
	}

	// Check if there's a camera cut track in the level sequence
	UMovieSceneCameraCutTrack* CameraCutTrack = GetCameraCutTrackFromLevelSequence(LevelSequencePath, bOutSuccess,
																				  OutInfoMessage);
	if (CameraCutTrack == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Link Camera To Camera Cut Track Failed - Camera cut track isn't valid. '%s'"), *LevelSequencePath);
		return;
	}

	// add camera actor in level sequence
	FGuid Guid = AddActorIntoLevelSequence(CameraActor, LevelSequencePath, bOutSuccess, OutInfoMessage);

	if (!Guid.IsValid())
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Link Camera To Camera Cut Track Failed - Failed to add camera actor in level sequence. '%s'"), *LevelSequencePath);
		return;
	}

	// Load level sequence
	ULevelSequence* LevelSequence = Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr,
																		  *LevelSequencePath));

	// Calculate the Tick Value for the input frame numbers.
	// Level Sequence works in ticks, not in frames and quantity of ticks varies based on TickResolution and DisplayRate.
	int FrameTickValue = LevelSequence->MovieScene->GetTickResolution().AsDecimal() / LevelSequence->MovieScene->GetDisplayRate().AsDecimal();

	// Link camera to camera cut track
	UMovieSceneCameraCutSection* Section = CameraCutTrack->AddNewCameraCut(UE::MovieScene::FRelativeObjectBindingID(Guid), FFrameNumber(StartFrame * FrameTickValue));

	if (Section == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Link Camera To Camera Cut Track Failed - Was not able to create Section '%s'"), *LevelSequencePath);
		return;
	}

	// Set end frame
	if (EndFrame > StartFrame)
	{
		Section->SetEndFrame(FFrameNumber(EndFrame * FrameTickValue));
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(
		TEXT("Link Camera To Camera Cut Track Succeeded - %s"), *LevelSequencePath);
}

UMovieScene3DTransformTrack* UMVAbilitySystemBPFLibrary::GetTransformTrackFromActorInLevelSequence(
	FString LevelSequencePath, AActor* Actor, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Get Actor Guid
	FGuid Guid = GetActorGuidFromLevelSequence(Actor, LevelSequencePath, bOutSuccess, OutInfoMessage);

	if (!Guid.IsValid())
	{
		return nullptr;
	}

	// Load level sequence
	ULevelSequence* LevelSequence = Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr,
	                                                                      *LevelSequencePath));

	// Get the transform track
	UMovieScene3DTransformTrack* TransformTrack = LevelSequence->MovieScene->FindTrack<
		UMovieScene3DTransformTrack>(Guid);

	bOutSuccess = TransformTrack != nullptr;
	const FString SucceededOrFailed = bOutSuccess ? "Succeeded" : "Failed";
	OutInfoMessage = FString::Printf(
		TEXT("Get Transform Track From Actor In Level Sequence %s - %s"), *SucceededOrFailed, *LevelSequencePath);

	return TransformTrack;
}

UMovieScene3DTransformTrack* UMVAbilitySystemBPFLibrary::AddTransformTrackToActorInLevelSequence(
	FString LevelSequencePath, AActor* Actor, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Check if there's a transform track in the level sequence
	UMovieScene3DTransformTrack* TransformTrack = GetTransformTrackFromActorInLevelSequence(
		LevelSequencePath, Actor, bOutSuccess, OutInfoMessage);

	if (TransformTrack != nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Add Transform Track To Actor In Level Sequence Failed - Track already in level sequence. '%s'"),
			*LevelSequencePath);
		return TransformTrack;
	}

	// Get actor Guid
	FGuid Guid = GetActorGuidFromLevelSequence(Actor, LevelSequencePath, bOutSuccess, OutInfoMessage);

	if (!Guid.IsValid())
	{
		return nullptr;
	}

	// Load level sequence
	ULevelSequence* LevelSequence = Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr,
	                                                                      *LevelSequencePath));

	// Add track
	TransformTrack = LevelSequence->MovieScene->AddTrack<UMovieScene3DTransformTrack>(Guid);

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(
		TEXT("Add Transform Track To Actor In Level Sequence Succeeded - %s"), *LevelSequencePath);
	return TransformTrack;
}

void UMVAbilitySystemBPFLibrary::RemoveTransformTrackFromActorInLevelSequence(FString LevelSequencePath,
	AActor* Actor, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Check if there's a transform track in the level sequence
	UMovieScene3DTransformTrack* TransformTrack = GetTransformTrackFromActorInLevelSequence(
		LevelSequencePath, Actor, bOutSuccess, OutInfoMessage);

	if (TransformTrack == nullptr)
	{
		return;
	}

	// Load level sequence
	ULevelSequence* LevelSequence = Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr,
	                                                                      *LevelSequencePath));

	// Remove track
	LevelSequence->MovieScene->RemoveTrack(*TransformTrack);

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(
		TEXT("Remove Transform Track From Actor In Level Sequence Succeeded - %s"), *LevelSequencePath);
}

UMovieScene3DTransformSection* UMVAbilitySystemBPFLibrary::GetTransformSectionFromActorInLevelSequence(
	FString LevelSequencePath, AActor* Actor, int SectionIndex, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Check if there's a transform track in the level sequence
	UMovieScene3DTransformTrack* TransformTrack = GetTransformTrackFromActorInLevelSequence(
		LevelSequencePath, Actor, bOutSuccess, OutInfoMessage);

	if (TransformTrack == nullptr)
	{
		return nullptr;
	}

	// Get all sections
	TArray<UMovieSceneSection*> AllSections = TransformTrack->GetAllSections();

	// Make sure the index is valid
	if (SectionIndex < 0 || SectionIndex >= AllSections.Num())
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Get Transform Section From Actor In Level Sequence Failed - Invalid Section Index. '%s'"),
			*LevelSequencePath);
		return nullptr;
	}

	// Return section
	bOutSuccess = true;
	OutInfoMessage = FString::Printf(
		TEXT("Get Transform Section From Actor In Level Sequence Succeeded - %s"), *LevelSequencePath);

	return Cast<UMovieScene3DTransformSection>(AllSections[SectionIndex]);
}

UMovieScene3DTransformSection* UMVAbilitySystemBPFLibrary::AddTransformSectionToActorInLevelSequence(
	FString LevelSequencePath, AActor* Actor, int StartFrame, int EndFrame, EMovieSceneBlendType BlendType,
	bool& bOutSuccess, FString& OutInfoMessage)
{
	// Check if there's a transform track in the level sequence
	UMovieScene3DTransformTrack* TransformTrack = GetTransformTrackFromActorInLevelSequence(
		LevelSequencePath, Actor, bOutSuccess, OutInfoMessage);

	if (TransformTrack == nullptr)
	{
		return nullptr;
	}

	// Create section
	UMovieScene3DTransformSection* TransformSection = Cast<UMovieScene3DTransformSection>(
		TransformTrack->CreateNewSection());

	if (TransformSection == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Add Transform Section To Actor In Level Sequence Failed - Failed to create new section. '%s'"),
			*LevelSequencePath);
		return nullptr;
	}

	// Calculate the amount of Ticks Per Frame for the input frame numbers.
	// Level Sequence works in ticks, not in frames and quantity of ticks varies based on TickResolution and DisplayRate.
	ULevelSequence* LevelSequence = Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr,
	                                                                      *LevelSequencePath));
	int TicksPerFrame = LevelSequence->MovieScene->GetTickResolution().AsDecimal() / LevelSequence->MovieScene->
		GetDisplayRate().AsDecimal();

	// Set frame range of the section
	TransformSection->SetRange(TRange<FFrameNumber>(FFrameNumber(StartFrame * TicksPerFrame),
	                                                FFrameNumber(EndFrame * TicksPerFrame)));

	// Set blend type
	TransformSection->SetBlendType(BlendType);

	// Place the section on a new row so it doesn't fight against another section
	int RowIndex = -1;
	for (UMovieSceneSection* ExistingSection : TransformTrack->GetAllSections())
	{
		RowIndex = FMath::Max(RowIndex, ExistingSection->GetRowIndex());
	}
	TransformSection->SetRowIndex(RowIndex + 1);

	// Add section to track
	TransformTrack->AddSection(*TransformSection);

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(
		TEXT("Add Transform Section To Actor In Level Sequence Succeeded - %s"), *LevelSequencePath);
	return TransformSection;
}

void UMVAbilitySystemBPFLibrary::RemoveTransformSectionFromActorInLevelSequence(FString LevelSequencePath,
	AActor* Actor, int SectionIndex, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Check if there's a transform section in the level sequence
	UMovieScene3DTransformSection* TransformSection = GetTransformSectionFromActorInLevelSequence(
		LevelSequencePath, Actor, SectionIndex, bOutSuccess, OutInfoMessage);

	if (TransformSection == nullptr)
	{
		bOutSuccess = false;
		return;
	}

	// Get Track
	UMovieScene3DTransformTrack* TransformTrack = GetTransformTrackFromActorInLevelSequence(
		LevelSequencePath, Actor, bOutSuccess, OutInfoMessage);

	// Remove section
	TransformTrack->RemoveSection(*TransformSection);

	// Refresh level sequence
	TransformTrack->Modify();

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(
		TEXT("Remove Transform Section From Actor In Level Sequence Succeeded - %s"), *LevelSequencePath);
}

void UMVAbilitySystemBPFLibrary::AddTransformKeyframe(FString LevelSequencePath, AActor* Actor, int SectionIndex,
                                                        int Frame, FTransform Transform, int KeyInterpolation,
                                                        bool& bOutSuccess, FString& OutInfoMessage)
{
	// Get the section
	UMovieScene3DTransformSection* Section = GetTransformSectionFromActorInLevelSequence(
		LevelSequencePath, Actor, SectionIndex, bOutSuccess, OutInfoMessage);

	if (Section == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Add Transform Keyframe Failed - Transform section is not valid. '%s'"), *LevelSequencePath);
		return;
	}

	// Remove previous keyframe is there's one
	RemoveTransformKeyframe(LevelSequencePath, Actor, SectionIndex, Frame, bOutSuccess, OutInfoMessage);

	// Location
	AddKeyframeToDoubleChannel(Section, 0, Frame, Transform.GetLocation().X, KeyInterpolation, bOutSuccess,
	                           OutInfoMessage);
	AddKeyframeToDoubleChannel(Section, 1, Frame, Transform.GetLocation().Y, KeyInterpolation, bOutSuccess,
	                           OutInfoMessage);
	AddKeyframeToDoubleChannel(Section, 2, Frame, Transform.GetLocation().Z, KeyInterpolation, bOutSuccess,
	                           OutInfoMessage);
	// Rotation
	AddKeyframeToDoubleChannel(Section, 3, Frame, Transform.Rotator().Roll, KeyInterpolation, bOutSuccess,
	                           OutInfoMessage);
	AddKeyframeToDoubleChannel(Section, 4, Frame, Transform.Rotator().Pitch, KeyInterpolation, bOutSuccess,
	                           OutInfoMessage);
	AddKeyframeToDoubleChannel(Section, 5, Frame, Transform.Rotator().Yaw, KeyInterpolation, bOutSuccess,
	                           OutInfoMessage);
	// Scale
	AddKeyframeToDoubleChannel(Section, 6, Frame, Transform.GetScale3D().X, KeyInterpolation, bOutSuccess,
	                           OutInfoMessage);
	AddKeyframeToDoubleChannel(Section, 7, Frame, Transform.GetScale3D().Y, KeyInterpolation, bOutSuccess,
	                           OutInfoMessage);
	AddKeyframeToDoubleChannel(Section, 8, Frame, Transform.GetScale3D().Z, KeyInterpolation, bOutSuccess,
	                           OutInfoMessage);

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Add Transform Keyframe Succeeded - %s"), *LevelSequencePath);
}

void UMVAbilitySystemBPFLibrary::RemoveTransformKeyframe(FString LevelSequencePath, AActor* Actor, int SectionIndex,
                                                           int Frame, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Get the section
	UMovieScene3DTransformSection* Section = GetTransformSectionFromActorInLevelSequence(
		LevelSequencePath, Actor, SectionIndex, bOutSuccess, OutInfoMessage);

	if (Section == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(
			TEXT("Add Transform Keyframe Failed - Transform section is not valid. '%s'"), *LevelSequencePath);
		return;
	}

	// Location
	RemoveKeyframeFromChannel(Section, 0, Frame, bOutSuccess, OutInfoMessage);
	RemoveKeyframeFromChannel(Section, 1, Frame, bOutSuccess, OutInfoMessage);
	RemoveKeyframeFromChannel(Section, 2, Frame, bOutSuccess, OutInfoMessage);
	// Rotation
	RemoveKeyframeFromChannel(Section, 3, Frame, bOutSuccess, OutInfoMessage);
	RemoveKeyframeFromChannel(Section, 4, Frame, bOutSuccess, OutInfoMessage);
	RemoveKeyframeFromChannel(Section, 5, Frame, bOutSuccess, OutInfoMessage);
	// Scale
	RemoveKeyframeFromChannel(Section, 6, Frame, bOutSuccess, OutInfoMessage);
	RemoveKeyframeFromChannel(Section, 7, Frame, bOutSuccess, OutInfoMessage);
	RemoveKeyframeFromChannel(Section, 8, Frame, bOutSuccess, OutInfoMessage);

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Remove Transform Keyframe Succeeded - %s"), *LevelSequencePath);
}

void UMVAbilitySystemBPFLibrary::AddKeyframeToDoubleChannel(UMovieSceneSection* Section, int ChannelIndex, int Frame,
                                                              double Value, int KeyInterpolation, bool& bOutSuccess,
                                                              FString& OutInfoMessage)
{
	// Make sure the section is valid
	if (Section == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Add Keyframe To Double Channel Failed - Section is not valid."));
		return;
	}

	// Get the channel
	FMovieSceneDoubleChannel* Channel = Section->GetChannelProxy().GetChannel<FMovieSceneDoubleChannel>(ChannelIndex);
	if (Channel == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Add Keyframe To Double Channel Failed - Channel is not valid."));
		return;
	}

	// Calculate the amount of Ticks Per Frame for the input frame numbers.
	// Level Sequence works in ticks, not in frames and quantity of ticks varies based on TickResolution and DisplayRate.
	ULevelSequence* LevelSequence = Cast<ULevelSequence>(Section->GetOutermostObject());
	int TicksPerFrame = LevelSequence->MovieScene->GetTickResolution().AsDecimal() / LevelSequence->MovieScene->
		GetDisplayRate().AsDecimal();
	FFrameNumber FrameNumber = FFrameNumber(Frame * TicksPerFrame);

	// Add key to channel
	if (KeyInterpolation == 0)
	{
		Channel->AddCubicKey(FrameNumber, Value);
	}
	else if (KeyInterpolation == 1)
	{
		Channel->AddLinearKey(FrameNumber, Value);
	}
	else
	{
		Channel->AddConstantKey(FrameNumber, Value);
	}

	// Refresh section
	Section->Modify();

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Add Keyframe To Double Channel Succeeded."));
}

void UMVAbilitySystemBPFLibrary::RemoveKeyframeFromChannel(UMovieSceneSection* Section, int ChannelIndex, int Frame,
                                                             bool& bOutSuccess, FString& OutInfoMessage)
{
	// Make sure section is valid
	if (Section == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Remove Keyframe From Channel Failed - Section is not valid."));
		return;
	}

	// Get the channel
	FMovieSceneChannel* Channel = Section->GetChannelProxy().GetChannel<FMovieSceneChannel>(ChannelIndex);
	if (Channel == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Remove Keyframe From Channel Failed - Channel is not valid."));
		return;
	}

	// Calculate the amount of Ticks Per Frame for the input frame numbers.
	// Level Sequence works in ticks, not in frames and quantity of ticks varies based on TickResolution and DisplayRate.
	ULevelSequence* LevelSequence = Cast<ULevelSequence>(Section->GetOutermostObject());
	int TicksPerFrame = LevelSequence->MovieScene->GetTickResolution().AsDecimal() / LevelSequence->MovieScene->
		GetDisplayRate().AsDecimal();
	FFrameNumber FrameNumber = FFrameNumber(Frame * TicksPerFrame);

	// Find key we want to remove
	TArray<FFrameNumber> UnusedKeyTimes;
	TArray<FKeyHandle> KeyHandles;
	Channel->GetKeys(TRange<FFrameNumber>(FrameNumber, FrameNumber), &UnusedKeyTimes, &KeyHandles);

	// Remove key
	Channel->DeleteKeys(KeyHandles);

	// Refresh section
	Section->Modify();

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Remove Keyframe From Channel Succeeded."));
}

void UMVAbilitySystemBPFLibrary::StartLevelSequenceRender(FString LevelSequencePath, FString OutputDirectory,
                                                            bool bRenderAsMovie, bool& bOutSuccess,
                                                            FString& OutInfoMessage)
{
	// Load Level Sequence
	ULevelSequence* LevelSequence = Cast<ULevelSequence>(StaticLoadObject(ULevelSequence::StaticClass(), nullptr,
																		  *LevelSequencePath));
	// Validate Level Sequence
	if (LevelSequence == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Start Level Sequence Render Failed - Level Sequence is not valid."));
		return;
	}

	// Create Capture Settings (Same as Render Movie Settings window)
	UAutomatedLevelSequenceCapture* Capture = NewObject<UAutomatedLevelSequenceCapture>();

	// Level Sequence
	Capture->LevelSequenceAsset = LevelSequence;

	// Output Directory
	FDirectoryPath DirPath;
	DirPath.Path = OutputDirectory;
	Capture->Settings.OutputDirectory = DirPath;

	// Render Type
	if (bRenderAsMovie)
	{
		Capture->SetImageCaptureProtocolType(UVideoCaptureProtocol::StaticClass());
		if (UVideoCaptureProtocol* VideoProtocol = Cast<UVideoCaptureProtocol>(Capture->ImageCaptureProtocol))
		{
			VideoProtocol->bUseCompression = true;
			VideoProtocol->CompressionQuality = 50;
		}
		else
		{
			bOutSuccess = false;
			OutInfoMessage = FString::Printf(TEXT("Start Level Sequence Render Failed - Video Capture Protocol is not valid."));
			return;
		}
		// Possible Classes: UNullAudioCaptureProtocol, UMasterAudioSubmixCaptureProtocol
		Capture->SetAudioCaptureProtocolType(UNullAudioCaptureProtocol::StaticClass());
	}
	else
	{
		// Possible Classes: UImageSequenceProtocol_JPG, UImageSequenceProtocol_PNG, UImageSequenceProtocol_BMP, UImageSequenceProtocol_EXR
		Capture->SetImageCaptureProtocolType(UImageSequenceProtocol_PNG::StaticClass());
		if (UImageSequenceProtocol_PNG* ImageProtocol = Cast<UImageSequenceProtocol_PNG>(Capture->ImageCaptureProtocol))
		{
			ImageProtocol->CompressionQuality = 50;
		}
		else
		{
			bOutSuccess = false;
			OutInfoMessage = FString::Printf(TEXT("Start Level Sequence Render Failed - Image Sequence Protocol is not valid."));
			return;
		}
	}

	// MovieSceneCapture
	Capture->bUseSeparateProcess = true; // If true, set bCloseEditorWhenCaptureStarts, AdditionalCommandLineArguments & InheritedCommandLineArguments
	Capture->bCloseEditorWhenCaptureStarts = false;
	Capture->AdditionalCommandLineArguments = "-NOSCREENMESSAGES";
	Capture->InheritedCommandLineArguments = "-skipcompile";

	// FMovieSceneCaptureSettings
	Capture->Settings.GameModeOverride = nullptr;
	Capture->Settings.OutputFormat = "{shot}_{frame}";
	Capture->Settings.bOverwriteExisting = true;
	Capture->Settings.bUseRelativeFrameNumbers = false;
	Capture->Settings.HandleFrames = 0;
	Capture->Settings.ZeroPadFrameNumbers = 0;
	Capture->Settings.FrameRate = FFrameRate(15, 1);
	Capture->Settings.bUseCustomFrameRate = false; // If true, set CustomFrameRate
	Capture->Settings.Resolution = FCaptureResolution(320, 240);
	Capture->Settings.bEnableTextureStreaming = false;
	Capture->Settings.bCinematicEngineScalability = false;
	Capture->Settings.bCinematicMode = false; // If true, set bAllowMovement, bAllowTurning, bShowPlayer, bShowHUD
	Capture->Settings.bUsePathTracer = false; // If true, set PathTracerSamplePerPixel

	// UAutomatedLevelSequenceCapture
	Capture->ShotName = "MyRender";
	Capture->bUseCustomStartFrame = false; // If true, set CustomStartFrame
	Capture->bUseCustomEndFrame = false; // If true, set CustomEndFrame
	Capture->WarmUpFrameCount = 0;
	Capture->DelayBeforeWarmUp = 0.f;
	Capture->DelayBeforeShotWarmUp = 0.f;
	Capture->DelayEveryFrame = 0.f;
	Capture->bWriteEditDecisionList = false;
	Capture->bWriteFinalCutProXML = false;

	// ULevelSequenceBurnInOptions
	ULevelSequenceBurnInOptions* BurnIn = NewObject<ULevelSequenceBurnInOptions>(Capture);
	BurnIn->bUseBurnIn = true;
	Capture->BurnInOptions = BurnIn;

	// Start Render
	USequencerToolsFunctionLibrary::RenderMovie(Capture, FOnRenderMovieStopped());

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Start Level Sequence Render Succeeded."));
}