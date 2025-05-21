// Copyright Yizai MathVis

#pragma once

#include "CoreMinimal.h"
#include "Actor/SphereEffectActor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Evaluation/Blending/MovieSceneBlendType.h"
#include "MVAbilitySystemBPFLibrary.generated.h"

class ULevelSequence;
class ACameraActor;
class UMovieSceneCameraCutTrack;
class UMovieScene3DTransformTrack;
class UMovieScene3DTransformSection;
class UMovieSceneSection;

/**
 * 
 */
UCLASS()
class MATHVIS_API UMVAbilitySystemBPFLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	 * Spawn a SphereEffectActor
	 *
	 * @param WorldContextObject
	 * @param Transform
	 * @param bOutSuccess
	 * @param OutInfoMessage
	 *
	 * @return ASphereEffectActor*
	 */
	UFUNCTION(BlueprintCallable, Category="Geometry|SphereEffectActor")
	static ASphereEffectActor* CreateSphereEffectActor(UObject* WorldContextObject, FTransform Transform, bool& bOutSuccess, FString& OutInfoMessage);

	/**
	 * Get actor guid from level sequence
	 *
	 * @param Actor The actor to get from the level sequence
	 * @param LevelSequencePath The path of the level sequence asset: "/Game/Asset/LevelSequence/TemplateLevelSequence" (e.g.)
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 *
	 * @return The guid of the actor in the level sequence
	 */
	UFUNCTION(BlueprintCallable, Category="Level Sequence|Add Remove Actor From Level Sequence")
	static FGuid GetActorGuidFromLevelSequence(AActor* Actor, FString LevelSequencePath, bool& bOutSuccess, FString&
	OutInfoMessage);

	/**
	 * Add an actor into a level sequence
	 *
	 * @param Actor The actor to add in the level sequence
	 * @param LevelSequencePath The path of the level sequence asset: "/Game/Asset/LevelSequence/TemplateLevelSequence" (e.g.)
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 *
	 * @return The guid of the actor in the level sequence
	 */
	UFUNCTION(BlueprintCallable, Category="Level Sequence|Add Remove Actor From Level Sequence")
	static FGuid AddActorIntoLevelSequence(AActor* Actor, FString LevelSequencePath, bool& bOutSuccess, FString&
	OutInfoMessage);

	/**
	 * Remove an actor from a level sequence
	 *
	 * @param Actor The actor to remove from the level sequence
	 * @param LevelSequencePath The path of the level sequence asset: "/Game/Asset/LevelSequence/TemplateLevelSequence" (e.g.)
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 */
	UFUNCTION(BlueprintCallable, Category="Level Sequence|Add Remove Actor From Level Sequence")
	static void RemoveActorFromLevelSequence(AActor* Actor, FString LevelSequencePath, bool& bOutSuccess, FString&
	OutInfoMessage);

	/**
	 * Get a camera cut track from a level sequence
	 *
	 * @param LevelSequencePath The path of the level sequence asset: "/Game/Asset/LevelSequence/TemplateLevelSequence" (e.g.)
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 *
	 * @return The camera cut track
	 */
	UFUNCTION(BlueprintCallable, Category="Level Sequence|Add Remove Camera Cut Track From Level Sequence")
	static UMovieSceneCameraCutTrack* GetCameraCutTrackFromLevelSequence(FString LevelSequencePath, bool& bOutSuccess, FString& OutInfoMessage);

	/**
	 * Add a camera cut track to a level sequence
	 *
	 * @param LevelSequencePath The path of the level sequence asset: "/Game/Asset/LevelSequence/TemplateLevelSequence" (e.g.)
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 *
	 * @return The camera cut track
	 */
	UFUNCTION(BlueprintCallable, Category="Level Sequence|Add Remove Camera Cut Track From Level Sequence")
	static UMovieSceneCameraCutTrack* AddCameraCutTrackInLevelSequence(FString LevelSequencePath, bool& bOutSuccess, FString& OutInfoMessage);

	/**
	 * Remove a camera cut track from a level sequence
	 *
	 * @param LevelSequencePath The path of the level sequence asset: "/Game/Asset/LevelSequence/TemplateLevelSequence" (e.g.)
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 */
	UFUNCTION(BlueprintCallable, Category="Level Sequence|Add Remove Camera Cut Track From Level Sequence")
	static void RemoveCameraCutTrackFromLevelSequence(FString LevelSequencePath, bool& bOutSuccess, FString& OutInfoMessage);

	/**
	 * Link a camera to camera cut track in a level sequence
	 *
	 * @param LevelSequencePath The path of the level sequence asset: "/Game/Asset/LevelSequence/TemplateLevelSequence" (e.g.)
	 * @param CameraActor The camera actor to link to the track
	 * @param StartFrame Start frame of the camera section in the level sequence
	 * @param EndFrame End frame of the camera section in the level sequence
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 */
	UFUNCTION(BlueprintCallable, Category="Level Sequence|Add Remove Camera Cut Track From Level Sequence")
	static void LinkCameraToCameraCutTrack(FString LevelSequencePath, ACameraActor* CameraActor, int StartFrame, int EndFrame, bool& bOutSuccess, FString& OutInfoMessage);

	/**
	 * Get the transform track from an actor in a level sequence
	 *
	 * @param LevelSequencePath The path of the level sequence asset: "/Game/Asset/LevelSequence/TemplateLevelSequence" (e.g.)
	 * @param Actor The actor in the level sequence
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 */
	UFUNCTION(BlueprintCallable, Category="Level Sequence|Add Remove Transfrom Track In Level Sequence")
	static UMovieScene3DTransformTrack* GetTransformTrackFromActorInLevelSequence(FString LevelSequencePath, AActor* Actor, bool& bOutSuccess, FString&
		OutInfoMessage);

	/**
	 * Add a transform track to an actor in a level sequence
	 *
	 * @param LevelSequencePath The path of the level sequence asset: "/Game/Asset/LevelSequence/TemplateLevelSequence" (e.g.)
	 * @param Actor The actor in the level sequence
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 */
	UFUNCTION(BlueprintCallable, Category="Level Sequence|Add Remove Transfrom Track In Level Sequence")
	static UMovieScene3DTransformTrack* AddTransformTrackToActorInLevelSequence(FString LevelSequencePath, AActor* Actor, bool& bOutSuccess, FString&
		OutInfoMessage);

	/**
	 * Remove a transform track from an actor in a level sequence
	 *
	 * @param LevelSequencePath The path of the level sequence asset: "/Game/Asset/LevelSequence/TemplateLevelSequence" (e.g.)
	 * @param Actor The actor in the level sequence
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 */
	UFUNCTION(BlueprintCallable, Category="Level Sequence|Add Remove Transfrom Track In Level Sequence")
	static void RemoveTransformTrackFromActorInLevelSequence(FString LevelSequencePath, AActor* Actor, bool& bOutSuccess, FString&
		OutInfoMessage);

	/**
	 * Get the transform section from an actor in a level sequence
	 *
	 * @param LevelSequencePath The path of the level sequence asset: "/Game/Asset/LevelSequence/TemplateLevelSequence" (e.g.)
	 * @param Actor The actor in the level sequence
	 * @param SectionIndex Index of the section
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 */
	UFUNCTION(BlueprintCallable, Category="Level Sequence|Add Remove Transfrom Track In Level Sequence")
	static UMovieScene3DTransformSection* GetTransformSectionFromActorInLevelSequence(FString LevelSequencePath, AActor* Actor, int SectionIndex, bool& bOutSuccess, FString&
		OutInfoMessage);

	/**
	 * Add a transform section to an actor in a level sequence
	 *
	 * @param LevelSequencePath The path of the level sequence asset: "/Game/Asset/LevelSequence/TemplateLevelSequence" (e.g.)
	 * @param Actor The actor in the level sequence
	 * @param StartFrame Start frame of the section
	 * @param EndFrame End frame of the section
	 * @param BlendType Blend type of the section
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 *
	 * @return The transform section
	 */
	UFUNCTION(BlueprintCallable, Category="Level Sequence|Add Remove Transfrom Track In Level Sequence")
	static UMovieScene3DTransformSection* AddTransformSectionToActorInLevelSequence(FString LevelSequencePath, AActor* Actor, int StartFrame, int EndFrame, EMovieSceneBlendType BlendType,
		bool& bOutSuccess, FString& OutInfoMessage);

	/**
	 * Remove a transform section from an actor in a level sequence
	 *
	 * @param LevelSequencePath The path of the level sequence asset: "/Game/Asset/LevelSequence/TemplateLevelSequence" (e.g.)
	 * @param Actor The actor in the level sequence
	 * @param SectionIndex Index of the section
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 */
	UFUNCTION(BlueprintCallable, Category="Level Sequence|Add Remove Transfrom Track In Level Sequence")
	static void RemoveTransformSectionFromActorInLevelSequence(FString LevelSequencePath, AActor* Actor, int SectionIndex, bool& bOutSuccess, FString&
		OutInfoMessage);

	/**
	 * Add a keyframe to a transform section in a level sequence
	 *
	 * @param LevelSequencePath The path of the level sequence asset: "/Game/Asset/LevelSequence/TemplateLevelSequence" (e.g.)
	 * @param Actor The actor in the level sequence
	 * @param SectionIndex Index of the section
	 * @param Frame Frame number
	 * @param Transform Value to apply to the keys
	 * @param KeyInterpolation Interpolation of the keys: 0=Cubic, 1=Linear, 2=Constant
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 */
	UFUNCTION(BlueprintCallable, Category="Level Sequence|Add Remove Transform Keyframe In Level Sequence")
	static void AddTransformKeyframe(FString LevelSequencePath, AActor* Actor, int SectionIndex, int Frame, FTransform Transform, int KeyInterpolation,
		bool& bOutSuccess, FString& OutInfoMessage);

	/**
	 * Remove a keyframe from a transform section in a level sequence
	 *
	 * @param LevelSequencePath The path of the level sequence asset: "/Game/Asset/LevelSequence/TemplateLevelSequence" (e.g.)
	 * @param Actor The actor in the level sequence
	 * @param SectionIndex Index of the section
	 * @param Frame Frame number
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 */
	UFUNCTION(BlueprintCallable, Category="Level Sequence|Add Remove Transform Keyframe In Level Sequence")
	static void RemoveTransformKeyframe(FString LevelSequencePath, AActor* Actor, int SectionIndex, int Frame, bool& bOutSuccess, FString&
		OutInfoMessage);

	/**
	 * Add a keyframe to a double channel in a level sequence
	 *
	 * @param Section Section to modify
	 * @param ChannelIndex Index of the channel
	 * @param Frame Frame number
	 * @param Value Value to apply to the keyframe
	 * @param KeyInterpolation Interpolation of the keys: 0=Cubic, 1=Linear, 2=Constant
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 */
	UFUNCTION(BlueprintCallable, Category="Level Sequence|Add Remove Transform Keyframe In Level Sequence")
	static void AddKeyframeToDoubleChannel(UMovieSceneSection* Section, int ChannelIndex, int Frame, double Value, int KeyInterpolation,
		bool& bOutSuccess, FString& OutInfoMessage);

	/**
	 * Remove a keyframe from a channel in a level sequence
	 *
	 * @param Section Section to modify
	 * @param ChannelIndex Index of the channel
	 * @param Frame Frame number
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 */
	UFUNCTION(BlueprintCallable, Category="Level Sequence|Add Remove Transform Keyframe In Level Sequence")
	static void RemoveKeyframeFromChannel(UMovieSceneSection* Section, int ChannelIndex, int Frame, bool& bOutSuccess, FString&
		OutInfoMessage);

	/**
	 * Start a render process (Deprecated)
	 *
	 * @param LevelSequencePath The path of the level sequence asset: "/Game/Asset/LevelSequence/TemplateLevelSequence" (e.g.)
	 * @param OutputDirectory Where to save the output: "/Game/Asset/OutputVideo" (e.g.)
	 * @param bRenderAsMovie If true, will render a movie. Otherwise, will render individual frames
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 */
	UFUNCTION(BlueprintCallable, Category="Level Sequence|Render Level Sequence")
	static void StartLevelSequenceRender(FString LevelSequencePath, FString OutputDirectory, bool bRenderAsMovie, bool& bOutSuccess, FString& OutInfoMessage);
};