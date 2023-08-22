// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PanelWidget.h"
#include "Widgets/SCanvas.h"
#include "Widgets/SOverlay.h"

/**
 * 选项Item 本质是一个图片 + 单选框，用于表示是否可以连接
 */
//UCLASS()
class WFC2D_API SSelectItemWidget : public SOverlay
{
	//GENERATED_BODY()

public:
	SLATE_BEGIN_ARGS(SSelectItemWidget){}
	SLATE_END_ARGS() 
	
	void Construct(const FArguments& InArgs);
};
