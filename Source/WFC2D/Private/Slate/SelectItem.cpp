// Fill out your copyright notice in the Description page of Project Settings.


#include "Slate/SelectItem.h"
#include "Widgets/Input/SCheckBox.h"
#include "Core/WFC2DHelper.h"

void SSelectItem::Construct(const FArguments& InArgs)
{
	Direction = InArgs._Direction;
	
	ImageBrush.DrawAs = ESlateBrushDrawType::Image;

	ShowImage = SNew(SImage).Image(&ImageBrush);
	
	//OnConnectStateChanged = InArgs._OnConnectStateChanged;

	AddSlot()
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Fill)
	[
		ShowImage.ToSharedRef()
	];

	AddSlot()
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Fill)
	[
		SNew(SCheckBox)
		.IsChecked(this, &SSelectItem::IsConnected)
		.OnCheckStateChanged(this, &SSelectItem::TileConnectStateChanged)
	];
}

ECheckBoxState SSelectItem::IsConnected() const
{	
	bool bIsFind = UWFC2DHelper::IsConnect(KeyTileId, ConnectTileId, Direction.Get());
	return bIsFind ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void SSelectItem::TileConnectStateChanged(ECheckBoxState InNewRadioState)
{
	//OnConnectStateChanged.Execute(InNewRadioState == ECheckBoxState::Checked, Direction.Get());
	InNewRadioState == ECheckBoxState::Checked ? UWFC2DHelper::ConnectTile(KeyTileId, ConnectTileId, Direction.Get()) : UWFC2DHelper::DisconnectTile(KeyTileId, ConnectTileId, Direction.Get());
}

void SSelectItem::UpdateItemImage(const FString& TileIndex)
{
	ImageBrush.SetResourceObject(UWFC2DHelper::GetTileTexture(TileIndex));
}

void SSelectItem::UpdateConnectID(const FString& KeyTileID, const FString& ConnectTileID)
{
	KeyTileId = KeyTileID;
	ConnectTileId = ConnectTileID;
}
