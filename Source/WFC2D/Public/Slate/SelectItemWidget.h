// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SOverlay.h"

class SSelectItem;

struct SelectNode {
	int RowIndex;
	int ColIndex;
	ECellDirection Direction;
};

/**
 * 九宫格 显示一个Tile的上下左右、或者八方向的Tile关系
 */

class WFC2D_API SSelectItemWidget : public SOverlay
{
public:
	SLATE_BEGIN_ARGS(SSelectItemWidget){}
	SLATE_END_ARGS() 
	
	void Construct(const FArguments& InArgs);

	void UpdateKeyTile(const FString KeyTileIndex);
	void UpdateConnectTile(const FString ConnectTileIndex);

private:
	/* 用于显示 Key Tile 的 SImage 控件 */
	TSharedPtr<SImage> KeyTileImage;	
	FSlateBrush KeyTileBrush;

	TArray<TSharedPtr<SSelectItem>> SelectTiles;
};
