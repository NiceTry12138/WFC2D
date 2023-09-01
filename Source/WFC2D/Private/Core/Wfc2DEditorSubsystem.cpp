// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Wfc2DEditorSubsystem.h"
#include "Core/Tile.h"
#include "Core/WFC2DHelper.h"
#include "Core/WFC2DCalModel.h"
#include "Serialization/JsonSerializer.h"

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
	
	// ECellDirection(((int)Direction + 2) % 4) 就是反向的意思，上变为下，左变为右
	// KeyTile的上面是 ConnectTile，那么ConnectTile的下面就是KeyTile 
	ConnectTile->ConnectId(ECellDirection(((int)Direction + 2) % 4), KeyTileId);
}

void UWfc2DEditorSubsystem::DisconnectTile(const FString& KeyTileId, const FString& ConnectTileId, ECellDirection Direction)
{
	UTile* KeyTile = GetTile(KeyTileId);
	UTile* ConnectTile = GetTile(ConnectTileId);

	KeyTile->DisconnectId(Direction, ConnectTileId);
	ConnectTile->DisconnectId(ECellDirection(((int)Direction + 2) % 4), KeyTileId);
}

FString UWfc2DEditorSubsystem::GetConnectConfig()
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	TArray<TSharedPtr<FJsonValue>> JsonValueArray;
	static const TArray<ECellDirection> DirectionEnums { ECellDirection::Top, ECellDirection::Right, ECellDirection::Bottom, ECellDirection::Left};
	for (const auto& Tile : Tiles) {
		TSharedPtr<FJsonObject> TileObject = MakeShareable(new FJsonObject);
		TileObject->SetStringField(TEXT("PackageName"), Tile->TileFullName.ToString());
		
		TArray<FString> Orients{ TEXT("Top"), TEXT("Right"), TEXT("Bottom"), TEXT("Left")};
		for (int OrientsIndex = 0; OrientsIndex < 4; ++OrientsIndex) {
			TArray<TSharedPtr<FJsonValue>> ConnectTiles;
			TArray<FString> PossibleIds;
			Tile->GetPossibleIds(DirectionEnums[OrientsIndex], PossibleIds);
			for (const auto Id : PossibleIds) {
				ConnectTiles.Add(MakeShareable(new FJsonValueString(GetTile(Id)->TileFullName.ToString())));
			}
			TileObject->SetArrayField(Orients[OrientsIndex], ConnectTiles);
		}

		JsonValueArray.Add(MakeShareable(new FJsonValueObject(TileObject)));
	}

	JsonObject->SetArrayField("Tiles", JsonValueArray);
	// 创建一个 JSON 字符串
	FString OutputString;

	// 创建一个 JSON 写入器
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);

	// 将 JSON 对象序列化为 JSON 字符串
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
	return OutputString;
}

bool UWfc2DEditorSubsystem::GenerationWFC2D(TArray<TArray<FString>>& FinalMap)
{
	if (!CalModel) {
		CalModel = NewObject<UWFC2DCalModel>();
	}

	bool Result = CalModel->Run(Tiles, 5, 5, FinalMap);
	return Result;
}
