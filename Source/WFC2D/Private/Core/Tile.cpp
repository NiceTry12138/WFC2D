// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Tile.h"

void UTile::InitTile(UTexture2D* Texture, FName FullName)
{
	TileID = FullName.ToString();
	TileTexture = Texture;
	TileFullName = FullName;
}

void UTile::GetPossibleIds(ECellDirection Direction, TArray<FString> &PossibleIds) const
{
	PossibleIds.Empty();
	auto RealDirection = GetDirection(Direction);
	auto Result = PossibileIDsMap.Find(RealDirection);
	if (Result) {
		PossibleIds.Append(*Result);
	}
}

void UTile::ConnectId(ECellDirection Direction, const FString& Id)
{
	auto Arr = PossibileIDsMap.Find(Direction);
	if (Arr == nullptr) {
		auto NewArr = TArray<FString>();
		NewArr.Add(Id);
		PossibileIDsMap.Add(Direction, NewArr);
	}
	else {
		Arr->Add(Id);
	}
}

void UTile::DisconnectId(ECellDirection Direction, const FString& Id)
{
	auto Arr = PossibileIDsMap.Find(Direction);
	if (Arr == nullptr) {
		return;
	}
	Arr->Remove(Id);
}

ECellDirection UTile::GetDirection(ECellDirection In) const
{
	return ECellDirection(((int)Rotate + (int)In) % 4);
}