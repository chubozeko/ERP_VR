// Fill out your copyright notice in the Description page of Project Settings.

#include "BPFL_JsonLoader.h"

FExemplarData UBPFL_JsonLoader::LoadFromJsonString(FString JsonString)
{
	FString result;
	FExemplarData EData;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		TSharedPtr<FJsonObject> JsonValueObject = JsonObject;

		EData.Exemplar_id = JsonValueObject->GetStringField(TEXT("exemplar_id"));
		EData.Rating = JsonValueObject->GetNumberField(TEXT("rating"));
		EData.Response_time_category = JsonValueObject->GetStringField(TEXT("response_time_category"));
		EData.Response_time_rating = JsonValueObject->GetStringField(TEXT("response_time_rating"));

		TSharedPtr<FJsonObject> catObj = JsonValueObject->GetObjectField(TEXT("category"));
		EData.Category.Beach = catObj->GetBoolField(TEXT("beach"));
		EData.Category.City_street = catObj->GetBoolField(TEXT("city_street"));
		EData.Category.Forest = catObj->GetBoolField(TEXT("forest"));
		EData.Category.None = catObj->GetBoolField(TEXT("none"));

		// UE_LOG(LogTemp, Warning, TEXT("Exemplar Id: %s, Rating: %d, Category=Forest: %d"), *EData.Exemplar_id, EData.Rating, EData.Category.Forest);
	}

	return EData;

}