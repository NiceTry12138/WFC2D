// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SOverlay.h"
#include "Core/WFC2DConfig.h"
//#include "Widgets/Input/SButton.h"
//#include "Components/Button.h"
//#include "SelectItem.generated.h"

/**
 * 选项Item 本质是一个图片 + 单选框，用于表示是否可以连接
 */

class WFC2D_API SSelectItem : public SOverlay
{
	//GENERATED_BODY()

public:
	SLATE_BEGIN_ARGS(SSelectItem)
	{}
		/* 当前Item显示的Tile的Index */
		SLATE_ATTRIBUTE(FString, ItemIndex)

		/* 当前选中的Tile的Index */
		SLATE_ATTRIBUTE(FString, KeyItemIndex)

		/* 当前Item的方位 */
		SLATE_ATTRIBUTE(ECellDirection, Direction)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	/* 用于初始时判断连接性，当前Tile与目标Tile可以连接，则为true */
	ECheckBoxState IsConnected() const;

	/* 通过点击CheckBox，修改Tile之间的连接性 */
	void TileConnectStateChanged(ECheckBoxState InNewRadioState);

	void UpdateItemImage(const FString& TileIndex);

private:
	TSharedPtr<SWidget> ShowImage;
	//TSharedPtr<SWidget> CheckBox;

	bool bIsChecked{false};

	TAttribute<FString> ItemIndex;
	TAttribute<FString> KeyItemIndex;
	TAttribute<ECellDirection> Direction;

	FSlateBrush ImageBrush;
};
