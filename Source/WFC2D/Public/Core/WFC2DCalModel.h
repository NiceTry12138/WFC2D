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

	void Reset(const TArray<FString>& NewPossible) { 
		PossibleTileIndexs = NewPossible; 
		bIsSelected = false; 
		bWasHandled = false; 
	}

	void Collapse() { 
		bIsSelected = true; 
		TileIndex = PossibleTileIndexs[FMath::RandHelper(PossibleTileIndexs.Num())]; 
		PossibleTileIndexs.Empty(); 
		PossibleTileIndexs.Push(TileIndex);  
	}

	void Constrain(const FString& InValidIndex) { 
		PossibleTileIndexs.Remove(InValidIndex); 
	}

	FString LogString() const { 
		FString Result;

		Result.Append(TEXT("X = "));
		Result.Append(FString::FromInt(X));

		Result.Append(TEXT(" Y = "));
		Result.Append(FString::FromInt(Y));


		if (bIsSelected) {
			Result.Append(TEXT(" Selected Index = "));
			Result.Append(TileIndex);
		}
		else {
			Result.Append(TEXT(" UnSelected"));
		}

		Result.Append(TEXT(" PossibleTileIndexs : [ "));

		for (const auto& PossibleIndex : PossibleTileIndexs) {
			Result.Append(PossibleIndex);
			Result.Append(TEXT(" "));
		}

		Result.Append(TEXT("]"));

		return Result;
	}

	bool operator ==(const FCell& Other) const
	{
		return X == Other.X && Y == Other.Y;
	}

	bool operator !=(const FCell& Other) const
	{
		return X != Other.X || Y != Other.Y;
	}
public:
	int X;		// 横轴坐标
	int Y;		// 纵轴坐标

	TArray<FString> PossibleTileIndexs;

	FString TileIndex;
	bool bIsSelected { false };
	bool bWasHandled { false };
};

/**
 * 
 */
UCLASS()
class WFC2D_API UWFC2DCalModel : public UObject
{
	GENERATED_BODY()
	
public:
	bool Run(const TArray<UTile*> Tiles, int WidghConfig, int HeightConfig, TArray<TArray<FString>>& FinalMap);

protected:

	/* 传播 */
	void Propagate(const FCell& SelectCell);

	/* 坍塌 */
	void Collapse(FCell& SelectCell);

	/* 是否全部坍缩 */
	bool IsFullyCollapsed();

	/* 获得熵值最小的方格坐标 */
	bool GetMinEntropy(FCell& FindCell);

	/* 还原全部Cell 重新坍塌 */
	void ResetCells();

	///* 回溯，本版本遇到错误直接全部重新开始，不计算回溯 */
	//void Backtrack();

	void GetValidNeighborCells(FCell SelectCell, TArray<FCell>& NeighborCells);

	bool IsTileCompatible(const FString& TileIndex1, const FString& TileIndex2, ECellDirection Direction);

	/* 返回 Cell2 在 Cell1 的 上下左右 */
	ECellDirection GetDirection(const FCell& Cell1, const FCell& Cell2);

	void LogInfo();
private:
	TArray<FString> PossibleTileIndex;

	TArray<TArray<FCell>> Cells;

	int IteratorIndex { 0 };

	int RowNum;
	int ColNum;

	/* 重新计算次数限制 */
	int ResetNum{10};
};
