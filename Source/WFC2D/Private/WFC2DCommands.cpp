// Copyright Epic Games, Inc. All Rights Reserved.

#include "WFC2DCommands.h"

#define LOCTEXT_NAMESPACE "FWFC2DModule"

void FWFC2DCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "WFC2D", "Bring up WFC2D window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
