// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WFC2DCalModel.h"
#include "Core/WFC2DHelper.h"
#include "Core/Tile.h"

void UWFC2DCalModel::Run(const TArray<UTile*> Tiles, int WidghConfig, int HeightConfig)
{
	// 目标是 200 * 100 的地图，那么有200列，100行，所以widgh对应的行应该是 HeightConfig
	RowNum = HeightConfig;
	ColNum = WidghConfig;

	PossibleTileIndex.Empty();
	for (const auto& Tile : Tiles) {
		PossibleTileIndex.Add(Tile->GetIndex());
	}

	Cells.Reset();
	Cells.Reserve(RowNum);

	for (int RowIndex = 0; RowIndex < RowNum; ++RowNum) {
		TArray<FCell> RowCells;
		RowCells.Reserve(ColNum);
		for (int ColIndex = 0; ColIndex < ColNum; ++ColIndex) {
			
		}
	}

	FCell Cell;
	while (!IsFullyCollapsed()) {
		bool bIsFind = GetMinEntropy(Cell);
		Collapse(Cell.X, Cell.Y);
		Propagate(Cell.X, Cell.Y);
	}
}

void UWFC2DCalModel::Propagate(int X, int Y)
{
	
}

void UWFC2DCalModel::Collapse(int X, int Y)
{
	
}

bool UWFC2DCalModel::IsFullyCollapsed()
{
	for (const auto& RowCells : Cells) {
		for (const auto& Cell : RowCells) {
			if (!Cell.bIsSelected) {
				return false;
			}
		}
	}
	return true;
}

bool UWFC2DCalModel::GetMinEntropy(FCell FindCell)
{
	int MinEntropy = INT_MAX;
	TArray<FCell> MinEntropyCells;	// 最低熵值相同 可能有多个 

	for (int RowIndex = 0; RowIndex < ColNum; ++RowIndex) {
		for (int ColIndex = 0; ColIndex < ColNum; ++ColIndex) {
			FCell Cell = Cells[RowIndex][ColIndex];
			if (Cell.bIsSelected) {
				continue;
			}
			if (Cell.PossibleTileIndexs.Num() < MinEntropy) {
				MinEntropy = Cell.PossibleTileIndexs.Num();
				MinEntropyCells.Empty();
			}
			if (MinEntropy == Cell.PossibleTileIndexs.Num()) {
				MinEntropyCells.Add(Cell);
			}
		}
	}

	if (MinEntropy == 0 || MinEntropyCells.Num() == 0) {
		return false;
	}

	// 随机返回其中一个最小的
	int MinCellIndex = FMath::RandHelper(MinEntropyCells.Num());
	FindCell = MinEntropyCells[MinCellIndex];

	return true;
}
