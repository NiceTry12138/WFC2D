// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TestFunctionLibraray.generated.h"

USTRUCT(BlueprintType)
struct FTileConfig {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture;
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class WFC2D_API UTestFunctionLibraray : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void GenerationTileInWorld(TArray<FTileConfig>& Tiles);

	UFUNCTION(BlueprintCallable)
	static void GenerationTileInWorld_1(FTileConfig& Tiles);
};
