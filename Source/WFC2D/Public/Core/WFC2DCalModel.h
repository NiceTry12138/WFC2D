// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
//#include "Core/WFC2DConfig.h"

#include "WFC2DCalModel.generated.h"

class UTile;

//USTRUCT()
struct FCell {
public:
	

public:
	int X;		// 横轴坐标
	int Y;		// 纵轴坐标

	TArray<FString> PossibleTileIndexs;

	FString TileIndex;
	bool bIsSelected { false };
};

/**
 * 
 */
UCLASS()
class WFC2D_API UWFC2DCalModel : public UObject
{
	GENERATED_BODY()
	
public:
	void Run(const TArray<UTile*> Tiles, int WidghConfig, int HeightConfig);

	/* 传播 */
	void Propagate(int X, int Y);

	/* 坍塌 */
	void Collapse(int X, int Y);

	/* 是否全部坍缩 */
	bool IsFullyCollapsed();

	/* 获得熵值最小的方格坐标 */
	bool GetMinEntropy(FCell FindCell);

	///* 回溯，本版本遇到错误直接全部重新开始，不计算回溯 */
	//void Backtrack();

private:
	TArray<FString> PossibleTileIndex;

	TArray<TArray<FCell>> Cells;

	int RowNum;
	int ColNum;
};
