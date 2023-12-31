// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/WFC2DHelper.h"
#include "Core/Wfc2DEditorSubsystem.h"
#include "Core/Tile.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonSerializer.h"
#include "AssetRegistry/AssetRegistryModule.h"

static const FVector2D TileSize = FVector2D(100, 100);

void UWFC2DHelper::InitTiles(const FName& ImportPath, TArray<UTile*> &Tiels)
{
	// 定义过滤器 细化查找
	FARFilter Filter;
	Filter.PackagePaths.Add(ImportPath);
	//Filter.ClassNames.Add(UTexture::StaticClass()->GetFName());	// 5.1 之后属性被弃用
	Filter.ClassPaths.Add(UTexture2D::StaticClass()->GetClassPathName());
	Filter.bRecursivePaths = true;
	Filter.bRecursiveClasses = true;

	TArray<FAssetData> AssetArray;
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::GetModuleChecked<FAssetRegistryModule>("AssetRegistry");
	AssetRegistryModule.Get().GetAssets(Filter, AssetArray);

	Tiels.Empty();


	UWfc2DEditorSubsystem* Wfc2DEditorSubsystem = UWFC2DHelper::GetWfc2dEditorSubsystem();

	for (const auto& AssetData : AssetArray) {		
		UE_LOG(LogTemp, Log, TEXT("Wfc2d Plugin => Find Texture Path: %s"), *AssetData.AssetName.ToString());
		FStringAssetReference TexturePath = AssetData.PackageName.ToString();
		UTexture2D* TileTexture = Cast<UTexture2D>(TexturePath.TryLoad());

		if (!TileTexture) {
			UE_LOG(LogTemp, Warning, TEXT("Wfc2d Plugin => Load %s Faild"), *AssetData.PackageName.ToString());
			continue;
		}

		auto Tile = NewObject<UTile>();
		//Tile->InitTile(Wfc2DEditorSubsystem->GetTileIndex(), TileTexture, AssetData.PackageName);
		Tile->InitTile(TileTexture, AssetData.PackageName);
		//Tile->TileFullName = AssetData.PackageName;

		Tiels.Push(Tile);
	}
}

UWfc2DEditorSubsystem* UWFC2DHelper::GetWfc2dEditorSubsystem()
{
	UWfc2DEditorSubsystem* Wfc2DEditorSubsystem = GEditor->GetEditorSubsystem<UWfc2DEditorSubsystem>();
	if (!Wfc2DEditorSubsystem) {
		UE_LOG(LogTemp, Warning, TEXT("Wfc2d Plugin => Can't Find UWfc2DEditorSubsystem"));
	}
	return Wfc2DEditorSubsystem;
}

UTexture2D* UWFC2DHelper::GetTileTexture(const FString& TileIndex)
{
	auto Tile = UWFC2DHelper::GetWfc2dEditorSubsystem()->GetTile(TileIndex);

	return Tile->GetTexture();
}

bool UWFC2DHelper::IsConnect(const FString& KeyTile, const FString& ConnectTile, ECellDirection Direction)
{
	return GetWfc2dEditorSubsystem()->IsConnect(KeyTile, ConnectTile, Direction);
}

void UWFC2DHelper::ConnectTile(const FString& KeyTile, const FString& ConnectTile, ECellDirection Direction)
{
	GetWfc2dEditorSubsystem()->ConnectTile(KeyTile, ConnectTile, Direction);
}

void UWFC2DHelper::DisconnectTile(const FString& KeyTile, const FString& ConnectTile, ECellDirection Direction)
{
	GetWfc2dEditorSubsystem()->DisconnectTile(KeyTile, ConnectTile, Direction);
}

void UWFC2DHelper::ExportConnectConfig()
{
	FString JsonContent = GetWfc2dEditorSubsystem()->GetConnectConfig();
	FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()).Append(TEXT("Wfc2dConnectConfig.json"));

	FFileHelper::SaveStringToFile(JsonContent, *ThePath);
}

bool UWFC2DHelper::GenerationWfc2d(TArray<TArray<FString>>& FinalMap)
{
	bool bIsSuccess = GetWfc2dEditorSubsystem()->GenerationWFC2D(FinalMap);

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	TArray<TSharedPtr<FJsonValue>> JsonValueArray;
	for (int RowIndex = 0; RowIndex < FinalMap.Num(); ++RowIndex) {
		for (int ColIndex = 0; ColIndex < FinalMap[RowIndex].Num(); ++ColIndex) {
			TSharedPtr<FJsonObject> TileObject = MakeShareable(new FJsonObject);
			TileObject->SetNumberField("RowIndex", RowIndex);
			TileObject->SetNumberField("ColIndex", ColIndex);
			TileObject->SetStringField("PackageName", FinalMap[RowIndex][ColIndex]);
			JsonValueArray.Add(MakeShareable(new FJsonValueObject(TileObject)));
		}
	}

	JsonObject->SetArrayField("Tiles", JsonValueArray);
	// 创建一个 JSON 字符串
	FString OutputString;

	// 创建一个 JSON 写入器
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);

	// 将 JSON 对象序列化为 JSON 字符串
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()).Append(TEXT("Wfc2dMap.json"));
	FFileHelper::SaveStringToFile(OutputString, *ThePath);

	return bIsSuccess;
}
