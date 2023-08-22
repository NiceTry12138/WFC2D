// Fill out your copyright notice in the Description page of Project Settings.


#include "Slate/SelectItemWidget.h"
#include "Styling/AppStyle.h"
#include "Widgets/Layout/SGridPanel.h"

#define LOCTEXT_NAMESPACE "SelectItemWidget"

void SSelectItemWidget::Construct(const FArguments& InArgs)
{
	auto GridPanel = SNew(SGridPanel);

	for (int Row = 0; Row < 3; ++Row) {
		GridPanel->SetRowFill(Row, 1.0);
		for (int Column = 0; Column < 3; ++Column) {
			GridPanel->SetColumnFill(Column, 1.0);
			GridPanel->AddSlot(Row, Column, SGridPanel::Layer(1))
			[
				SNew(SImage)
				.Image(FAppStyle::GetBrush("Icons.ChevronDown"))
			];
		}
	}

	AddSlot()
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Fill)
	[
		GridPanel
	];
}

#undef LOCTEXT_NAMESPACE