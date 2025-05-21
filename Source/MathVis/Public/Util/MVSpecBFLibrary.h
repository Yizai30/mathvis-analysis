// Copyright Yizai MathVis

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "MVSpecBFLibrary.generated.h"

// class FJsonObject;

USTRUCT(BlueprintType, Category="Struct|Keyframe")
struct FKeyframe
{
	GENERATED_BODY()

// These variables are visible in both Blueprint and Json
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|Keyframe")
	double FrameNum = 0.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|Keyframe")
	FString Shape = "Default";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|Keyframe")
	TArray<FString> EdgeLabels = {};
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|Keyframe")
	FString Content = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|Keyframe")
	TMap<FString, float> Location = {
		{TEXT("X"), 0.0f},
		{TEXT("Y"), 0.0f},
		{TEXT("Z"), 0.0f}
	};
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|Keyframe")
	TMap<FString, float> Rotation = {
		{TEXT("X"), 0.0f},
		{TEXT("Y"), 0.0f},
		{TEXT("Z"), 0.0f}
	};
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|Keyframe")
	TMap<FString, float> Scale = {
		{TEXT("X"), 0.0f},
		{TEXT("Y"), 0.0f},
		{TEXT("Z"), 0.0f}
	};
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|Keyframe")
	TMap<FString, float> Color = {
		{TEXT("R"), 0.0f},
		{TEXT("G"), 0.0f},
		{TEXT("B"), 0.0f}
	};
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|Keyframe")
	float Opacity = 1.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|Keyframe")
	bool Visible = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|Keyframe")
	FString MaterialPath = "Default";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|Keyframe")
	FString AnimationPath = "Default";
};

USTRUCT(BlueprintType, Category="Struct|Keyframe")
struct FKeyframeList
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Struct|Keyframe")
	TArray<FKeyframe> Keyframes = {};
};

/**
 * 
 */
UCLASS()
class MATHVIS_API UMVSpecBFLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Open a text file and read its content
	 *
	 * @param FilePath The path of your file
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 *
	 * @return The string content of your file
	 */
	UFUNCTION(BlueprintCallable, Category="Util|Read Write File")
	static FString ReadStringFromFile(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage);

	/**
	 * Create a text file with content
	 *
	 * @param FilePath The path of your file
	 * @param String The string to want to write in the file
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 */
	UFUNCTION(BlueprintCallable, Category="Util|Read Write File")
	static void WriteStringToFile(FString FilePath, FString String, bool& bOutSuccess, FString& OutInfoMessage);

	/**
	 * Open a json file, read its content and convert it into a JsonObject
	 *
	 * @param JsonFilePath The path of the json file: "/Game/Asset/Json/TemplateJson.json" (e.g.)
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 *
	 * @return The JsonObject content of the json file
	 */
	static TSharedPtr<FJsonObject> ReadJson(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage);

	/**
	 * Convert a JsonObject to a string, create a json file and dump the string in it
	 *
	 * @param JsonFilePath The path of the json file: "/Game/Asset/Json/TemplateJson.json" (e.g.)
	 * @param JsonObject The JsonObject to want to write in the file
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 */
	static void WriteJson(FString JsonFilePath, TSharedPtr<FJsonObject> JsonObject, bool& bOutSuccess, FString&
	OutInfoMessage);

	/**
	 * Open a json file, read its content and dump it into a structure
	 *
	 * @param JsonFilePath The path of the json file: "/Game/Asset/Json/TemplateJson.json" (e.g.)
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 *
	 * @return The structure content of your json file
	 */
	UFUNCTION(BlueprintCallable, Category="Util|Read Write File")
	static FKeyframeList ReadKeyframeListStructFromJsonFile(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage);

	/**
	 * Convert a structure to a string, create a json file and dump the string in it
	 *
	 * @param JsonFilePath The path of the json file: "/Game/Asset/Json/TemplateJson.json" (e.g.)
	 * @param KeyframeList The struct to want to write in the file
	 * @param bOutSuccess If the action was a success or not
	 * @param OutInfoMessage More information about the action's result
	 */
	UFUNCTION(BlueprintCallable, Category="Util|Read Write File")
	static void WriteKeyframeListStructToJsonFile(FString JsonFilePath, FKeyframeList KeyframeList, bool& bOutSuccess, FString& OutInfoMessage);
};