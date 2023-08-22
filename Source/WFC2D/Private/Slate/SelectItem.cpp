// Fill out your copyright notice in the Description page of Project Settings.


#include "Slate/SelectItem.h"
#include "Widgets/Input/SCheckBox.h"

void SSelectItem::Construct(const FArguments& InArgs)
{
	ShowImage = SNew(SImage).Image(FAppStyle::GetBrush(TEXT("Icons.PlusCircle")));
	//CheckBox = SNew(SCheckBox);

	AddSlot()
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Fill)
	[
		ShowImage.ToSharedRef()
		//SNew(SImage).
		//Image(FAppStyle::GetBrush(TEXT("Icons.PlusCircle")))
	];

	AddSlot()
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Fill)
	[
		SNew(SCheckBox)
	];
}
