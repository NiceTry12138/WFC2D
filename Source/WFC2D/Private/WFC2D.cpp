// Copyright Epic Games, Inc. All Rights Reserved.

#include "WFC2D.h"
#include "WFC2DStyle.h"
#include "WFC2DCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

#include "Core/Tile.h"
#include "Core/WFC2DHelper.h"
#include "Core/Wfc2DEditorSubsystem.h"

#include "Slate/TilesList.h"
#include "Slate/SelectItemWidget.h"

static const FName WFC2DTabName("WFC2D");

#define LOCTEXT_NAMESPACE "FWFC2DModule"

void FWFC2DModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FWFC2DStyle::Initialize();
	FWFC2DStyle::ReloadTextures();

	FWFC2DCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FWFC2DCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FWFC2DModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FWFC2DModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(WFC2DTabName, FOnSpawnTab::CreateRaw(this, &FWFC2DModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FWFC2DTabTitle", "WFC2D"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FWFC2DModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FWFC2DStyle::Shutdown();

	FWFC2DCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(WFC2DTabName);
}

TSharedRef<SDockTab> FWFC2DModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FWFC2DModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("WFC2D.cpp"))
		);

	//TArray<UTile*> Tiles;
	//UWFC2DHelper::InitTiles(FName("/Game/Arts/Tiles"), Tiles);

	//auto Img = UWFC2DHelper::CreateTileImage(Tiles[0]);

	UWFC2DHelper::GetWfc2dEditorSubsystem()->InitTiles(FName("/Game/Arts/Tiles"));

	ConnectConfigWidget = SNew(SSelectItemWidget);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(STextBlock)
					.Text(FText(LOCTEXT("FWFC2DModuleKeyTile", "选择主方块")))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(STilesList)
					.OnSelectTileChanged_Raw(this, &FWFC2DModule::UpdateSelectTile)
					.TileIndexs(UWFC2DHelper::GetWfc2dEditorSubsystem()->GetTileIndexs())
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(STextBlock)
					.Text(FText(LOCTEXT("FWFC2DModuleConnectTile", "选择关联方块")))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(STilesList)
					.OnSelectTileChanged_Raw(this, &FWFC2DModule::UpdateSelectConnectTile)
					.TileIndexs(UWFC2DHelper::GetWfc2dEditorSubsystem()->GetTileIndexs())
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(STextBlock)
					.Text(FText(LOCTEXT("FWFC2DModuleConfigTile", "配置关联性")))
				]
				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				[
					ConnectConfigWidget.ToSharedRef()
				]
				+ SVerticalBox::Slot()
				.AutoHeight() 
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					[
						SNew(SButton)
						.Text(LOCTEXT("FWFC2DModuleExport", "导入关联关系"))
						.OnClicked_Raw(this, &FWFC2DModule::ImporTileConnectInfo)
					]
					+ SHorizontalBox::Slot()
					[
						SNew(SButton)
						.Text(LOCTEXT("FWFC2DModuleExport", "导出关联关系"))
						.OnClicked_Raw(this, &FWFC2DModule::GenerationTileConnectInfo)
					]
					+ SHorizontalBox::Slot()
					[
						SNew(SButton)
						.Text(LOCTEXT("FWFC2DModuleGenerate", "开始生成"))
						.OnClicked_Raw(this, &FWFC2DModule::GenerationTileMap)
					]
				]
			]
		];
}

void FWFC2DModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(WFC2DTabName);
}

void FWFC2DModule::UpdateSelectTile(FString TileIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("TileList Select -> %s"), *TileIndex);
	ConnectConfigWidget->UpdateKeyTile(TileIndex);
}

void FWFC2DModule::UpdateSelectConnectTile(FString TileIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("TileList Connect Select -> %s"), *TileIndex);
	ConnectConfigWidget->UpdateConnectTile(TileIndex);
}

FReply FWFC2DModule::ImporTileConnectInfo()
{
	return FReply::Handled();
}

FReply FWFC2DModule::GenerationTileMap()
{
	//UE_LOG(LogTemp, Log, TEXT("ProjectDir %s"), *FPaths::ProjectDir());
	//UE_LOG(LogTemp, Log, TEXT("ConvertRelativePathToFull ProjectDir %s"), *FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()));
	//UE_LOG(LogTemp, Log, TEXT("%s"), *FPaths:GameDir());
	TArray<TArray<FString>> FinalMap;
	bool bIsSuccess = UWFC2DHelper::GenerationWfc2d(FinalMap);

	if (!bIsSuccess) {
		return FReply::Handled();
	}

	return FReply::Handled();
}

FReply FWFC2DModule::GenerationTileConnectInfo()
{
	UWFC2DHelper::ExportConnectConfig();
	return FReply::Handled();
}

void FWFC2DModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FWFC2DCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FWFC2DCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWFC2DModule, WFC2D)