// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "JsonLoader.generated.h"

USTRUCT(BlueprintType)
struct FExemplarCategoryData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JsonData)
	bool Beach;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JsonData)
	bool City_street;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JsonData)
	bool Forest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JsonData)
	bool None;
};

USTRUCT(BlueprintType)
struct FExemplarData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JsonData)
	FExemplarCategoryData Category;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JsonData)
	FString Exemplar_id;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JsonData)
	int32 Rating;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JsonData)
	FString Response_time_category;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = JsonData)
	FString Response_time_rating;
};


UCLASS()
class ERP_VR_API AJsonLoader : public APawn
{
	GENERATED_BODY()

public:
	AJsonLoader();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = Json)
	void TestFunc_SaveToJson();

	UFUNCTION(BlueprintCallable, Category = Json)
	void TestFunc_LoadFromJson();

private:
	FVector ParseJsonAsVector(TSharedPtr<FJsonObject> JsonValueObject, FString KeyName);


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = JsonData)
	FExemplarData ExemplarData;
};
