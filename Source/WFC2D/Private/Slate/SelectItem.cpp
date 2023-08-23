// Fill out your copyright notice in the Description page of Project Settings.


#include "Slate/SelectItem.h"
#include "Widgets/Input/SCheckBox.h"

void SSelectItem::Construct(const FArguments& InArgs)
{
	ItemIndex = InArgs._ItemIndex;
	KeyItemIndex = InArgs._KeyItemIndex;
	Direction = InArgs._Direction;

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
		.IsChecked(this, &SSelectItem::IsConnected)
		.OnCheckStateChanged(this, &SSelectItem::TileConnectStateChanged)
	];

	//auto DirectionText = FText::FromString("NULL");

	//switch (Direction.Get())
	//{
	//case ECellDirection::Bottom:
	//	DirectionText = FText::FromString("Bottom");
	//	break;
	//case ECellDirection::Top:
	//	DirectionText = FText::FromString("Top");
	//	break;
	//case ECellDirection::Left:
	//	DirectionText = FText::FromString("Left");
	//	break;
	//case ECellDirection::Right:
	//	DirectionText = FText::FromString("Right");
	//	break;
	//}

	//AddSlot()
	//.HAlign(HAlign_Fill)
	//.VAlign(VAlign_Fill)
	//[
	//	SNew(STextBlock)
	//	.Text(DirectionText)
	//];
}

ECheckBoxState SSelectItem::IsConnected() const
{
	return bIsChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void SSelectItem::TileConnectStateChanged(ECheckBoxState InNewRadioState)
{
	switch (InNewRadioState)
	{
	case ECheckBoxState::Unchecked:
		UE_LOG(LogTemp, Warning, TEXT("Unchecked"));
		bIsChecked = false;
		break;
	case ECheckBoxState::Checked:
		UE_LOG(LogTemp, Warning, TEXT("Checked"));
		bIsChecked = true;
		break;
	case ECheckBoxState::Undetermined:
		UE_LOG(LogTemp, Warning, TEXT("Undetermined"));
		break;
	}
}
