// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SOverlay.h"
#include "Core/WFC2DConfig.h"

/**
 * 
 */
class WFC2D_API STilesList : public SOverlay
{
public:
	SLATE_BEGIN_ARGS(STilesList){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	
	void OnTileSelected(TSharedPtr<FString> InItem, ESelectInfo::Type InSelectInfo);

	TSharedRef<class ITableRow> OnTileRow(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable) const;
private:
	TArray<TSharedPtr<FString>> TileIndexs;
	
};
