// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WFC2DHelper.generated.h"

class UTile;
class UWfc2DEditorSubsystem;

/**
 * 
 */
UCLASS(BlueprintType)
class WFC2D_API UWFC2DHelper : public UObject
{
	GENERATED_BODY()
	
public:
	/* 通过输入的路径，遍历其中所有 UTexture 对象，并初始化到抽成 Tile 数组 */
	static void InitTiles(const FName& ImportPath, TArray<UTile*> &Tiels);

	static UWfc2DEditorSubsystem* GetWfc2dEditorSubsystem();

	static UTexture2D* GetTileTexture(const FString& TileIndex);

	static bool IsConnect(const FString& KeyTile, const FString& ConnectTile, ECellDirection Direction);

	static void ConnectTile(const FString& KeyTile, const FString& ConnectTile, ECellDirection Direction);

	static void DisconnectTile(const FString& KeyTile, const FString& ConnectTile, ECellDirection Direction);
private:

};
