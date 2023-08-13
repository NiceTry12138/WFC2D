// Copyright Epic Games, Inc. All Rights Reserved.

#include "WFC2D.h"
#include "WFC2DStyle.h"
#include "WFC2DCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

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

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FWFC2DModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(WFC2DTabName);
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