// Fill out your copyright notice in the Description page of Project Settings.


#include "Slate/SelectItemWidget.h"
#include "Slate/SelectItem.h"
#include "Styling/AppStyle.h"
#include "Widgets/Layout/SGridPanel.h"
#include "Components/PanelWidget.h"
#include "Core/WFC2DHelper.h"

#define LOCTEXT_NAMESPACE "SelectItemWidget"

void SSelectItemWidget::Construct(const FArguments& InArgs)
{
	auto GridPanel = SNew(SGridPanel);

	for (int Index = 0; Index < 3; ++Index) {
		GridPanel->SetRowFill(Index, 1.0f);
		GridPanel->SetColumnFill(Index, 1.0f);
	}

	static const TArray<SelectNode> SelectTilesNodes = {
		{0, 1, ECellDirection::Top}, 
		{2, 1, ECellDirection::Bottom}, 
		{1, 0, ECellDirection::Left}, 
		{1, 2, ECellDirection::Right}
	};

	for (const auto& NodeConfig : SelectTilesNodes) {
		auto SelectItem = SNew(SSelectItem)
							.Direction(NodeConfig.Direction)
							.Visibility(EVisibility::Hidden);
		GridPanel->AddSlot(NodeConfig.ColIndex, NodeConfig.RowIndex, SGridPanel::Layer(1))
		[
			SelectItem
		];
		SelectTiles.Add(SelectItem);
	}

	KeyTileBrush.DrawAs = ESlateBrushDrawType::Image;

	KeyTileImage = SNew(SImage)
					.Image(&KeyTileBrush)
					.Visibility(EVisibility::Hidden);

	GridPanel->AddSlot(1, 1, SGridPanel::Layer(1))
	[
		KeyTileImage.ToSharedRef()
	];


	AddSlot()
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Fill)
	[
		GridPanel
	];
}

void SSelectItemWidget::UpdateKeyTile(const FString& KeyTileIndex)
{
	KeyTileBrush.SetResourceObject(UWFC2DHelper::GetTileTexture(KeyTileIndex));

	KeyTileImage->SetVisibility(EVisibility::Visible);

	KeyTileID = KeyTileIndex;
	UpdateConnectTileID();
}

void SSelectItemWidget::UpdateConnectTile(const FString& ConnectTileIndex)
{
	for (auto Item : SelectTiles) {
		Item->UpdateItemImage(ConnectTileIndex);
		Item->SetVisibility(EVisibility::Visible);
	}

	ConnectTileID = ConnectTileIndex;
	UpdateConnectTileID();
}

void SSelectItemWidget::UpdateConnectTileID()
{
	for (auto Item : SelectTiles) {
		Item->UpdateConnectID(KeyTileID, ConnectTileID);
	}
}

#undef LOCTEXT_NAMESPACE