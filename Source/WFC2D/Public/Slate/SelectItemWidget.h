// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PanelWidget.h"
#include "Widgets/SOverlay.h"

/**
 * 九宫格 显示一个Tile的上下左右、或者八方向的Tile关系
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
