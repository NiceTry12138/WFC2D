// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WFC2DConfig.h"
#include "Tile.generated.h"

/**
 *
 */
UCLASS()
class WFC2D_API UTile : public UObject
{
	GENERATED_BODY()
public:
	void InitTile(int Id, UTexture2D* Texture);

	void GetPossibleIds(ECellDirection Direction, TArray<int> PossibleIds);		// 获取上面相连方块的可能性，由于旋转的问题，返回值不固定

	inline UTexture2D* GetTexture() { return TileTexture; }

protected:
	ECellDirection GetDirection(ECellDirection In);

public:
	/* 当前Tile的ID */
	UPROPERTY()
	int TileID;												

	/*  当前Tile的贴图 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* TileTexture { nullptr };					

private:
	/* 方向与其对应的可选的 Tile ID */
	TMap<ECellDirection, TArray<int>> PossibileIDsMap;		

	/* 默认无旋转 */
	ESpriteRotate Rotate{ ESpriteRotate::Rotate_0 };		
};