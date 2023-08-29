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
	FCell() {}
	FCell(int XConf, int YConf, const TArray<FString> PossibleTileIndexsConf): X(XConf), Y(YConf), PossibleTileIndexs(PossibleTileIndexsConf){  }

	void Reset(const TArray<FString>& NewPossible) { PossibleTileIndexs = NewPossible; bIsSelected = false; }

	void Collapse() { bIsSelected = true; TileIndex = PossibleTileIndexs[FMath::RandHelper(PossibleTileIndexs.Num())]; }

	void Constrain(const FString& InValidIndex) { PossibleTileIndexs.Remove(InValidIndex); }
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

protected:

	/* 传播 */
	void Propagate(const FCell& SelectCell);

	/* 坍塌 */
	void Collapse(FCell& SelectCell);

	/* 是否全部坍缩 */
	bool IsFullyCollapsed();

	/* 获得熵值最小的方格坐标 */
	bool GetMinEntropy(FCell FindCell);

	/* 还原全部Cell 重新坍塌 */
	void ResetCells();

	///* 回溯，本版本遇到错误直接全部重新开始，不计算回溯 */
	//void Backtrack();

	void GetValidNeighborCells(FCell SelectCell, TArray<FCell>& NeighborCells);

	bool IsTileCompatible(const FString& TileIndex1, const FString& TileIndex2, ECellDirection Direction);

	/* 返回 Cell2 在 Cell1 的 上下左右 */
	ECellDirection GetDirection(const FCell& Cell1, const FCell& Cell2);
private:
	TArray<FString> PossibleTileIndex;

	TArray<TArray<FCell>> Cells;

	int RowNum;
	int ColNum;

	/* 重新计算次数限制 */
	int ResetNum{10};
};
