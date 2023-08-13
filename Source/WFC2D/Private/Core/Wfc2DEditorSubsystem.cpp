// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Wfc2DEditorSubsystem.h"

FString UWfc2DEditorSubsystem::GetTileIndex()
{
	int TimeStamp = (FDateTime::Now() - FDateTime(1970, 1, 1)).GetTotalMilliseconds();
	int ID = ++Index;
	Index %= 10000;

	// 模拟一个雪花数： 0 + 机器号 + 时间戳 + ID
	return FString::FromInt(TimeStamp).Append(FString::FromInt(ID));
}