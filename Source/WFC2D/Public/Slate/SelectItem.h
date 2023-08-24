// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SOverlay.h"
#include "Core/WFC2DConfig.h"

// Called when the selection changes
//DECLARE_DELEGATE_TwoParams(FOnConnectStateChanged, bool, ECellDirection);

/**
 * 选项Item 本质是一个图片 + 单选框，用于表示是否可以连接
 */

class WFC2D_API SSelectItem : public SOverlay
{
	//GENERATED_BODY()

public:
	SLATE_BEGIN_ARGS(SSelectItem){}
		/* 当前Item的方位 */
		SLATE_ATTRIBUTE(ECellDirection, Direction)
		/* 当选项框连接性变化 */
		//SLATE_EVENT(FOnConnectStateChanged, OnConnectStateChanged)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	/* 用于初始时判断连接性，当前Tile与目标Tile可以连接，则为true */
	ECheckBoxState IsConnected() const;

	/* 通过点击CheckBox，修改Tile之间的连接性 */
	void TileConnectStateChanged(ECheckBoxState InNewRadioState);

	void UpdateItemImage(const FString& TileIndex);

	void UpdateConnectID(const FString& KeyTileID, const FString& ConnectTileID);

private:
	TSharedPtr<SWidget> ShowImage;
	//TSharedPtr<SWidget> CheckBox;

	TAttribute<ECellDirection> Direction;

	FSlateBrush ImageBrush;

	//FOnConnectStateChanged OnConnectStateChanged;

	FString KeyTileId;
	FString ConnectTileId;
};
