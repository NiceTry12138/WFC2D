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

const UTile* UWfc2DEditorSubsystem::GetTile(const FString& FileIndex) const
{
	// TODO: Tiles 应该使用 TSet/TMap 容器存储而不是TArray
	for (const auto& Tile : Tiles) {
		if (Tile->GetIndex().Equals(FileIndex)) {
			return Tile;
		}
	}
	return nullptr;
}
