// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "Wfc2DEditorSubsystem.generated.h"

class UTile;

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

	const UTile* GetTile(const FString& TileIndex) const;

private:
	int Index{ 0 };
	TArray<UTile*> Tiles;
};
