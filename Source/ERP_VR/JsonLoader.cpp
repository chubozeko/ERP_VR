// Fill out your copyright notice in the Description page of Project Settings.

#include "JsonLoader.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "Templates/SharedPointer.h"

AJsonLoader::AJsonLoader()
{
 	PrimaryActorTick.bCanEverTick = false;
}

void AJsonLoader::BeginPlay()
{
	Super::BeginPlay();

	// TestFunc_SaveToJson();
	TestFunc_LoadFromJson();
	
}

void AJsonLoader::TestFunc_SaveToJson() 
{
	FExemplarCategoryData cat;
	cat.Beach = true;
	cat.City_street = false;
	cat.Forest = false;
	cat.None = false;

	ExemplarData.Exemplar_id = TEXT("EXB000");
	ExemplarData.Rating = 5;
	ExemplarData.Response_time_category = TEXT("10/14/2022, 5:51:09 PM");
	ExemplarData.Response_time_rating = TEXT("10/14/2022, 5:51:14 PM");
	ExemplarData.Ex_category = cat;

	FString JsonString;
	FJsonObjectConverter::UStructToJsonObjectString(ExemplarData, JsonString);
	FFileHelper::SaveStringToFile(*JsonString, *(FPaths::ProjectContentDir() + TEXT("/Json/text.json")));
}

void AJsonLoader::TestFunc_LoadFromJson()
{
	FString JsonString;
	FFileHelper::LoadFileToString(JsonString, *(FPaths::ProjectContentDir() + TEXT("/Json/text.json")));

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid()) 
	{
		TSharedPtr<FJsonObject> JsonValueObject = JsonObject;

		FExemplarData EData;
		EData.Exemplar_id = JsonValueObject->GetStringField(TEXT("exemplar_id"));
		EData.Rating = JsonValueObject->GetNumberField(TEXT("rating"));
		EData.Response_time_category = JsonValueObject->GetStringField(TEXT("response_time_category"));
		EData.Response_time_rating = JsonValueObject->GetStringField(TEXT("response_time_rating"));

		TSharedPtr<FJsonObject> catObj = JsonValueObject->GetObjectField(TEXT("category"));
		EData.Ex_category.Beach = catObj->GetBoolField(TEXT("beach"));
		EData.Ex_category.City_street = catObj->GetBoolField(TEXT("city_street"));
		EData.Ex_category.Forest = catObj->GetBoolField(TEXT("forest"));
		EData.Ex_category.None = catObj->GetBoolField(TEXT("none"));

		// UE_LOG(LogTemp, Warning, TEXT("Exemplar Id: %s, Rating: %d, Category=Forest: %d"), *EData.Exemplar_id, EData.Rating, EData.Category.Forest);
	}
}

FVector ParseJsonAsVector(TSharedPtr<FJsonObject> JsonValueObject, FString KeyName) 
{
	TArray<FString> ArrayJson;
	JsonValueObject->TryGetStringArrayField(*KeyName, ArrayJson);
	return FVector{ FCString::Atof(*ArrayJson[0]), FCString::Atof(*ArrayJson[1]), FCString::Atof(*ArrayJson[2]) };
}