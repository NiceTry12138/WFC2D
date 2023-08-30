// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/TestFunctionLibraray.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonSerializer.h"

UTestFunctionLibraray::UTestFunctionLibraray(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UTestFunctionLibraray::GenerationTileInWorld(TArray<FTileConfig>& Tiles)
{
	TSharedPtr<FJsonObject> JsonObject;

	FString ThePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()).Append(TEXT("Wfc2dMap.json"));
	FString JsonContent;
	FFileHelper::LoadFileToString(JsonContent, *ThePath);

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonContent);
	FJsonSerializer::Deserialize(Reader, JsonObject);
	
	Tiles.Empty();

	const TArray<TSharedPtr<FJsonValue>>* TilesConfig;
	if (JsonObject->TryGetArrayField(TEXT("Tiles"), /*out*/ TilesConfig)) {
		for (TSharedPtr<FJsonValue> TileConfig : *TilesConfig)
		{
			int RowIndex = TileConfig->AsObject()->GetNumberField(TEXT("RowIndex"));
			int ColIndex = TileConfig->AsObject()->GetNumberField(TEXT("ColIndex"));
			FString PackageName = TileConfig->AsObject()->GetStringField(TEXT("PackageName"));

			FTileConfig TheConf;
			TheConf.X = RowIndex;
			TheConf.Y = ColIndex;

			FStringAssetReference TexturePathRef = PackageName;
			UTexture2D* TileTexture = Cast<UTexture2D>(TexturePathRef.TryLoad());
			if (!TileTexture) {
				UE_LOG(LogTemp, Log, TEXT("Can Find PackageName: %s"), *PackageName);
				continue;
			}
			TheConf.Texture = TileTexture; 

			Tiles.Add(TheConf);
		}
	}
}

void UTestFunctionLibraray::GenerationTileInWorld_1(FTileConfig& Tiles)
{
}
