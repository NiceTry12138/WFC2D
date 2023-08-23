// Fill out your copyright notice in the Description page of Project Settings.


#include "Slate/TilesList.h"
#include "Widgets/Views/SListView.h"

void STilesList::Construct(const FArguments& InArgs)
{

	TileIndexs.Add(TSharedPtr<FString>(new FString(TEXT("1____"))));
	TileIndexs.Add(TSharedPtr<FString>(new FString(TEXT("2____"))));
	TileIndexs.Add(TSharedPtr<FString>(new FString(TEXT("3____"))));
	TileIndexs.Add(TSharedPtr<FString>(new FString(TEXT("4____"))));
	TileIndexs.Add(TSharedPtr<FString>(new FString(TEXT("5____"))));
	TileIndexs.Add(TSharedPtr<FString>(new FString(TEXT("6____"))));
	
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
	UE_LOG(LogTemp, Warning, TEXT("TileList Select -> %s"), **InItem.Get());
}

TSharedRef<ITableRow> STilesList::OnTileRow(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable) const
{
	return
		SNew(SComboRow< TSharedRef<FString> >, OwnerTable)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(1)
			.Padding(2.0f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(*InItem))
				.Font(FAppStyle::GetFontStyle(TEXT("PropertyWindow.NormalFont")))
			]
		];
}