// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "WFC2DConfig.generated.h"

UENUM()
enum class ESpriteRotate : uint8
{
	Rotate_0 = 0,	// 图片旋转0° 就是原图片
	Rotate_90,		// 图片旋转90°
	Rotate_180,		// 图片旋转180°
	Rotate_270,		// 图片旋转270°
};

UENUM()
enum class ECellDirection : uint8
{
	Top = 0,	// 上
	Right,		// 右
	Bottom,		// 下
	Left,		// 左
};
