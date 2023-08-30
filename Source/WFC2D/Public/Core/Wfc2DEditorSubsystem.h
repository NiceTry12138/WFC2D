// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Wfc2DEditorSubsystem.generated.h"

class UTile;
class UWFC2DCalModel;

/**
 * 
 */
UCLASS()
class WFC2D_API UWfc2DEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	FString GetTileIndex();
	void InitTiles(const FName& FilePath);

	const TArray<UTile*>& GetTiles() const;
	TArray<FString> GetTileIndexs();

	UTile* GetTile(const FString& TileIndex) const;

	bool IsConnect(const FString& KeyTile, const FString& ConnectTile, ECellDirection Direction);

	void ConnectTile(const FString& KeyTile, const FString& ConnectTile, ECellDirection Direction);

	void DisconnectTile(const FString& KeyTile, const FString& ConnectTile, ECellDirection Direction);

	FString GetConnectConfig();

	bool GenerationWFC2D(TArray<TArray<FString>>& FinalMap);

private:
	int Index{ 0 };
	TArray<UTile*> Tiles;

	UWFC2DCalModel* CalModel;
};
