// Copyright Yizai MathVis


#include "Util/MVSpecBFLibrary.h"

#include "JsonObjectConverter.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"

FString UMVSpecBFLibrary::ReadStringFromFile(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Check if the file exists
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Read String From File Failed - File doesn't exist - '%s'"), *FilePath);
		return "";
	}

	FString RetString = "";

	// Try to read the file. Output goes int RetString
	if (!FFileHelper::LoadFileToString(RetString, *FilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Read String From File Failed - Was not able to read the file. Is this a text file? - '%s'"), *FilePath);
		return "";
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Read String From File Succeeded - '%s'"), *FilePath);
	return RetString;
}

void UMVSpecBFLibrary::WriteStringToFile(FString FilePath, FString String, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Try to write the string into the file
	if (!FFileHelper::SaveStringToFile(String, *FilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Write String To File Failed - Was not able to write to file. Is the file read only? Is the path valid? - '%s'"), *FilePath);
		return;
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Write String To File Succeeded - '%s'"), *FilePath);
}

TSharedPtr<FJsonObject> UMVSpecBFLibrary::ReadJson(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage)
{
	// Try to read Json file
	FString JsonString = ReadStringFromFile(JsonFilePath, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		return nullptr;
	}

	TSharedPtr<FJsonObject> RetJsonObject;

	// Try to convert string to json object. Output goes in RetJsonObject
	if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), RetJsonObject))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Read Json Failed - Was not able to deserialize the json string. Is it the right format? - '%s'"), *JsonString);
		return nullptr;
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Read Json Succeeded - '%s'"), *JsonFilePath);
	return RetJsonObject;
}

void UMVSpecBFLibrary::WriteJson(FString JsonFilePath, TSharedPtr<FJsonObject> JsonObject, bool& bOutSuccess,
	FString& OutInfoMessage)
{
	FString JsonString;

	// Try to convert json object to string. Output goes in JsonString
	if (!FJsonSerializer::Serialize(JsonObject.ToSharedRef(), TJsonWriterFactory<>::Create(&JsonString, 0)))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Write Json Failed - Was not able to serialize the json to string. Is the JsonObject valid?"));
		return;
	}

	// Try to write json string to file
	WriteStringToFile(JsonFilePath, JsonString, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		return;
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Write Json Succeeded - '%s'"), *JsonFilePath);
}

FKeyframeList UMVSpecBFLibrary::ReadKeyframeListStructFromJsonFile(FString JsonFilePath, bool& bOutSuccess,
	FString& OutInfoMessage)
{
	// Try to read generic json object from file
	TSharedPtr<FJsonObject> JsonObject = ReadJson(JsonFilePath, bOutSuccess, OutInfoMessage);
	if (!bOutSuccess)
	{
		return FKeyframeList();
	}

	FKeyframeList RetKeyframeList;

	// Try to convert generic json object to the desired structure. Output goes in RetKeyframeList
	if (!FJsonObjectConverter::JsonObjectToUStruct<FKeyframeList>(JsonObject.ToSharedRef(), &RetKeyframeList))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Read Keyframe List Struct From Json File Failed - Was not able to convert the json object to the desired structure. Is it the right format / struct? - '%s'"), *JsonFilePath);
		return FKeyframeList();
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Read Keyframe List Struct From Json File Succeeded - '%s'"), *JsonFilePath);
	return RetKeyframeList;
}

void UMVSpecBFLibrary::WriteKeyframeListStructToJsonFile(FString JsonFilePath, FKeyframeList KeyframeList,
	bool& bOutSuccess, FString& OutInfoMessage)
{
	// Try to convert struct to generic json object
	TSharedPtr<FJsonObject> JsonObject = FJsonObjectConverter::UStructToJsonObject(KeyframeList);
	if (JsonObject == nullptr)
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Write Keyframe List Struct To Json File Failed - Was not able to convert the struct to a json object."));
		return;
	}

	// Try to write to json file
	WriteJson(JsonFilePath, JsonObject, bOutSuccess, OutInfoMessage);
}