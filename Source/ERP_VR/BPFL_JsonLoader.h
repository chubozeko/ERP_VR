// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "JsonLoader.h"
#include "JsonObjectConverter.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFL_JsonLoader.generated.h"

UCLASS()
class ERP_VR_API UBPFL_JsonLoader : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
		UFUNCTION(BlueprintCallable, Category = "JSON", meta = (Keywords = "Json"))
		static FExemplarData LoadFromJsonString(FString JsonString);
};