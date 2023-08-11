// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WFC2DConfig.h"
#include "UTile.generated.h"

/**
 *
 */
UCLASS()
class WFC2DEDITOR_API UTile : public UObject
{
	GENERATED_BODY()
public:
	void InitTile(int Id, UTexture2D* Texture);

	void GetPossibleIds(ECellDirection Direction, TArray<int> PossibleIds);		// 获取上面相连方块的可能性，由于旋转的问题，返回值不固定

protected:
	ECellDirection GetDirection(ECellDirection In);

public:
	UPROPERTY()
	int TileID;												// 当前Tile的ID

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* TileTexture {nullptr};						// 当前Tile的贴图

private:
	TMap<ECellDirection, TArray<int>> PossibileIDsMap;		// 方向与其对应的可选的 Tile ID

	ESpriteRotate Rotate{ ESpriteRotate::Rotate_0 };		// 默认无旋转


};
