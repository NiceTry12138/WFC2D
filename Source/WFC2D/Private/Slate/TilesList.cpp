// Fill out your copyright notice in the Description page of Project Settings.


#include "Slate/TilesList.h"
#include "Widgets/Views/SListView.h"
#include "Core/WFC2DHelper.h"
#include "Core/Wfc2DEditorSubsystem.h"
#include "Core/Tile.h"

void STilesList::Construct(const FArguments& InArgs)
{
	OnSelectTileChanged = InArgs._OnSelectTileChanged;
	TileIndexsAttr = InArgs._TileIndexs;

	UpdateTileIndexs();
	UpdateTileBrush();

	AddSlot()
	[
		SNew(SListView< TSharedPtr<FString> >)
		.ListItemsSource(&TileIndexs)
		.Orientation(EOrientation::Orient_Horizontal)
		.OnGenerateRow(this, &STilesList::OnTileRow)
		.OnSelectionChanged(this, &STilesList::OnTileSelected)
	];
}

void STilesList::OnTileSelected(TSharedPtr<FString> InItem, ESelectInfo::Type InSelectInfo)
{
	//FString Index = *InItem.Get();
	if (!InItem) {
		return;
	}
	OnSelectTileChanged.Execute(*InItem.Get());
}

TSharedRef<ITableRow> STilesList::OnTileRow(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable) const
{
	auto Brsuh = TileBrushs.Find(*InItem);

	return
		SNew(SComboRow< TSharedRef<FString> >, OwnerTable)
		[
			//SNew(STextBlock)
			//.Text(FText::FromString(*InItem))
			//.Font(FAppStyle::GetFontStyle(TEXT("PropertyWindow.NormalFont")))
			SNew(SImage)
			.Image(Brsuh)
		];
}

void STilesList::UpdateTileIndexs()
{
	const int32 NumOptions = TileIndexsAttr.Get().Num() + 1;

	TileIndexs.Reset();
	TileIndexs.Reserve(NumOptions);

	for (const FString& Name : TileIndexsAttr.Get())
	{
		TileIndexs.Add(MakeShared<FString>(Name));
	}
}

void STilesList::UpdateTileBrush()
{
	TileBrushs.Empty();
	for (const auto& TileIndex : TileIndexs) {
		FSlateBrush ItemBrush;
		ItemBrush.SetResourceObject(UWFC2DHelper::GetTileTexture(*TileIndex.Get()));
		ItemBrush.DrawAs = ESlateBrushDrawType::Image;
		ItemBrush.ImageSize.X = 120;
		ItemBrush.ImageSize.Y = 120;

		TileBrushs.Add(*TileIndex.Get(), ItemBrush);
	}
}
