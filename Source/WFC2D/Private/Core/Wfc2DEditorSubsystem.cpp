// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Wfc2DEditorSubsystem.h"
#include "Core/WFC2DHelper.h"
#include "Core/Tile.h"

FString UWfc2DEditorSubsystem::GetTileIndex()
{
	int TimeStamp = (FDateTime::Now() - FDateTime(1970, 1, 1)).GetTotalMilliseconds();
	int ID = ++Index;
	Index %= 10000;

	// 模拟一个雪花数： 0 + 机器号 + 时间戳 + ID
	return FString::FromInt(TimeStamp).Append(FString::FromInt(ID));
}

void UWfc2DEditorSubsystem::InitTiles(const FName& FilePath)
{
	Tiles.Empty();
	UWFC2DHelper::InitTiles(FilePath, Tiles);
}

const TArray<UTile*>& UWfc2DEditorSubsystem::GetTiles() const
{
	return Tiles;
}

TArray<FString> UWfc2DEditorSubsystem::GetTileIndexs()
{
	TArray<FString> Result;
	for (const auto& Tile : Tiles) {
		Result.Add(Tile->GetIndex());
	}
	return Result;
}

UTile* UWfc2DEditorSubsystem::GetTile(const FString& FileIndex) const
{
	// TODO: Tiles 应该使用 TSet/TMap 容器存储而不是TArray
	for (const auto& Tile : Tiles) {
		if (Tile->GetIndex().Equals(FileIndex)) {
			return Tile;
		}
	}
	return nullptr;
}

bool UWfc2DEditorSubsystem::IsConnect(const FString& KeyTile, const FString& ConnectTile, ECellDirection Direction)
{
	auto Tile = GetTile(KeyTile);
	if (!Tile) {
		return false;
	}

	TArray<FString> ConnectTiles;
	Tile->GetPossibleIds(Direction, ConnectTiles);
	return ConnectTiles.Find(ConnectTile) != INDEX_NONE;
}

void UWfc2DEditorSubsystem::ConnectTile(const FString& KeyTileId, const FString& ConnectTileId, ECellDirection Direction)
{
	UTile* KeyTile = GetTile(KeyTileId);
	UTile* ConnectTile = GetTile(ConnectTileId);

	KeyTile->ConnectId(Direction, ConnectTileId);
	ConnectTile->ConnectId(ECellDirection(((int)Direction + 2) % 4), KeyTileId);
}

void UWfc2DEditorSubsystem::DisconnectTile(const FString& KeyTileId, const FString& ConnectTileId, ECellDirection Direction)
{
	UTile* KeyTile = GetTile(KeyTileId);
	UTile* ConnectTile = GetTile(ConnectTileId);

	KeyTile->DisconnectId(Direction, ConnectTileId);
	ConnectTile->DisconnectId(ECellDirection(((int)Direction + 2) % 4), KeyTileId);
}
