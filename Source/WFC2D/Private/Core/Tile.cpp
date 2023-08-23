// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Tile.h"

void UTile::InitTile(FString Id, UTexture2D* Texture)
{
	TileID = Id;
	TileTexture = Texture;
}

void UTile::GetPossibleIds(ECellDirection Direction, TArray<int> PossibleIds)
{
	PossibleIds.Empty();
	auto RealDirection = GetDirection(Direction);
	auto Result = PossibileIDsMap.Find(RealDirection);
	if (Result) {
		PossibleIds.Append(*Result);
	}
}

ECellDirection UTile::GetDirection(ECellDirection In)
{
	return ECellDirection(((int)Rotate + (int)In) % 4);
}