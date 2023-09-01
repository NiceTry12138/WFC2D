// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WFC2DCalModel.h"
#include "Core/WFC2DHelper.h"
#include "Core/Tile.h"

bool UWFC2DCalModel::Run(const TArray<UTile*> Tiles, int WidghConfig, int HeightConfig, TArray<TArray<FString>>& FinalMap)
{
	// 目标是 200 * 100 的地图，那么有200列，100行，所以widgh对应的行应该是 HeightConfig
	RowNum = HeightConfig;
	ColNum = WidghConfig;

	IteratorIndex = 0;

	PossibleTileIndex = TArray<FString>();
	PossibleTileIndex.Empty();
	for (const auto& Tile : Tiles) {
		PossibleTileIndex.Add(Tile->GetIndex());
	}

	Cells.Reset();
	Cells.Reserve(RowNum);

	for (int RowIndex = 0; RowIndex < RowNum; ++RowIndex) {
		TArray<FCell> RowCells;
		RowCells.Reserve(ColNum);
		for (int ColIndex = 0; ColIndex < ColNum; ++ColIndex) {
			FCell Cell(RowIndex, ColIndex, PossibleTileIndex);
			RowCells.Add(Cell);
		}
		Cells.Add(RowCells);
	}

	FCell Cell;
	while (!IsFullyCollapsed() && ResetNum > 0) {
		bool bIsFind = GetMinEntropy(Cell);

		if (!bIsFind) {
			--ResetNum;
			IteratorIndex = 0;
			ResetCells();
			UE_LOG(LogTemp, Warning, TEXT("WFC2D: Cal Faild %d ----------------------------------"), ResetNum);
			continue;
		}

		++IteratorIndex;

		Collapse(Cell);
		Propagate(Cell);

		LogInfo();
	}

	if (ResetNum <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("WFC2D: Cal Faild"));
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("WFC2D: Cal Success"));
	FinalMap.Empty();

	for (int RowIndex = 0; RowIndex < RowNum; ++RowIndex) {
		TArray<FString> RowIndexs;
		for (int ColIndex = 0; ColIndex < ColNum; ++ColIndex) {
			RowIndexs.Add(Cells[RowIndex][ColIndex].TileIndex);
		}
		FinalMap.Add(RowIndexs);
	}
	return true;
}

void UWFC2DCalModel::Propagate(const FCell& SelectCell)
{
	static TArray<FCell> ProcessCells;
	ProcessCells.Empty();
	ProcessCells.Push(Cells[SelectCell.X][SelectCell.Y]);

	TArray<FCell> NeighborCells;
	while (!ProcessCells.IsEmpty())
	{
		FCell CurCell = ProcessCells.Pop();
		GetValidNeighborCells(CurCell, NeighborCells);

		for (auto& Cell : NeighborCells) {
			if (Cells[Cell.X][Cell.Y].bWasHandled) {
				continue;
			}

			Cells[Cell.X][Cell.Y].bWasHandled = true;
			// Cell.bWasHandled = true; // 值传递 设置无效

			TArray<FString> InValidTileIndexs;
			for (const FString& NeighborCellTile : Cells[Cell.X][Cell.Y].PossibleTileIndexs) {
				bool bIsTileCompatible = false;
				for (const FString& CurCellTile : CurCell.PossibleTileIndexs) {
					bIsTileCompatible |= IsTileCompatible(CurCellTile, NeighborCellTile, GetDirection(CurCell, Cell));
				}
				if (!bIsTileCompatible) {
					InValidTileIndexs.Add(NeighborCellTile);
				}	
			}

			ProcessCells.Push(Cell);
			for (const auto& InValidIndex : InValidTileIndexs) {
				Cells[Cell.X][Cell.Y].Constrain(InValidIndex);
				//Cell.Constrain(InValidIndex); // 值传递 设置无效
			}
		}
	}

	for (int RowIndex = 0; RowIndex < RowNum; ++RowIndex) {
		for (int ColIndex = 0; ColIndex < ColNum; ++ColIndex) {
			Cells[RowIndex][ColIndex].bWasHandled = false;
		}
	}

}

void UWFC2DCalModel::Collapse(FCell& SelectCell)
{
	//SelectCell.Collapse();
	Cells[SelectCell.X][SelectCell.Y].Collapse();
}

bool UWFC2DCalModel::IsFullyCollapsed()
{
	int NoSelectedCellNum = 0;
	for (const auto& RowCells : Cells) {
		for (const auto& Cell : RowCells) {
			if (!Cell.bIsSelected) {
				//return false;
				NoSelectedCellNum++;
			}
		}
	}

	//return true;
	return NoSelectedCellNum == 0;
}

bool UWFC2DCalModel::GetMinEntropy(FCell& FindCell)
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

void UWFC2DCalModel::ResetCells()
{
	for (int RowIndex = 0; RowIndex < RowNum; ++RowIndex) {
		for (int ColIndex = 0; ColIndex < ColNum; ++ColIndex) {
			Cells[RowIndex][ColIndex].Reset(PossibleTileIndex);
		}
	}
}

void UWFC2DCalModel::GetValidNeighborCells(FCell SelectCell, TArray<FCell>& NeighborCells)
{
	NeighborCells.Empty();

	if (SelectCell.X + 1 < RowNum) {
		NeighborCells.Add(Cells[SelectCell.X + 1][SelectCell.Y]);
	}
	if (SelectCell.X - 1 >= 0) {
		NeighborCells.Add(Cells[SelectCell.X - 1][SelectCell.Y]);
	}
	if (SelectCell.Y + 1 < ColNum) {
		NeighborCells.Add(Cells[SelectCell.X][SelectCell.Y + 1]);
	}
	if (SelectCell.Y - 1 >= 0) {
		NeighborCells.Add(Cells[SelectCell.X][SelectCell.Y - 1]);
	}
}

bool UWFC2DCalModel::IsTileCompatible(const FString& TileIndex1, const FString& TileIndex2, ECellDirection Direction)
{
	return UWFC2DHelper::IsConnect(TileIndex1, TileIndex2, Direction);
}

ECellDirection UWFC2DCalModel::GetDirection(const FCell& Cell1, const FCell& Cell2)
{
	// X 表示行序号 所以 X 不同其实是上下不同 而不是高度不同
	// Y 表示列序号 所以 Y 不同其实是左右不同 而不是高度不同
	if (Cell1.X > Cell2.X) {
		return ECellDirection::Bottom;
	}
	if (Cell1.X < Cell2.X) {
		return ECellDirection::Top;
	}
	if (Cell1.Y > Cell2.Y) {
		return ECellDirection::Left;
	}
	if (Cell1.Y < Cell2.Y) {
		return ECellDirection::Right;
	}
	UE_LOG(LogTemp, Error, TEXT("WFC2D: Same Cell"));
	return ECellDirection();
}

void UWFC2DCalModel::LogInfo()
{
	UE_LOG(LogTemp, Log, TEXT("WFC2D: IteratorIndex = %d"), IteratorIndex);

	for (const auto& RowTiles : Cells) {
		for (const auto& Tile : RowTiles) {
			UE_LOG(LogTemp, Log, TEXT("%s"), *Tile.LogString());
		}
	}

	UE_LOG(LogTemp, Log, TEXT("================================================"));
}
