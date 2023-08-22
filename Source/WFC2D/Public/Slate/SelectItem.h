// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SOverlay.h"
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
	SLATE_BEGIN_ARGS(SSelectItem) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);


private:
	TSharedPtr<SWidget> ShowImage;
	//TSharedPtr<SWidget> CheckBox;
};
