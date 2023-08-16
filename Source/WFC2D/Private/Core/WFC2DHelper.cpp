// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WFC2DHelper.h"
#include "Core/Tile.h"
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

	for (const auto& AssetData : AssetArray) {		
		//UE_LOG(LogTemp, Log, TEXT("%s"), *AssetData.AssetName.ToString());
		FStringAssetReference TexturePath = AssetData.PackageName.ToString();
		UTexture2D* TileTexture = Cast<UTexture2D>(TexturePath.TryLoad());

		if (!TileTexture) {
			UE_LOG(LogTemp, Warning, TEXT("Load %s Faild"), *AssetData.PackageName.ToString());
			continue;
		}

		auto Tile = NewObject<UTile>();
		Tile->InitTile(1, TileTexture);

		Tiels.Push(Tile);
	}
}

TSharedRef<SImage> UWFC2DHelper::CreateTileImage(UTile* Tile)
{
	return SNew(SImage).
		Image(new FSlateDynamicImageBrush(Tile->GetTexture(), TileSize, FName("Tile")));
}

void UWFC2DHelper::CreateTileImage(TArray<UTile*> Tiles, TArray<TSharedRef<SImage>> TileImages)
{
	TileImages.Empty();
	for(auto Tile : Tiles)
	{
		TileImages.Push(CreateTileImage(Tile));
	}
}
