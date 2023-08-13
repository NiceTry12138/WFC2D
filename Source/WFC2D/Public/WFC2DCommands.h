// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "WFC2DStyle.h"

class FWFC2DCommands : public TCommands<FWFC2DCommands>
{
public:

	FWFC2DCommands()
		: TCommands<FWFC2DCommands>(TEXT("WFC2D"), NSLOCTEXT("Contexts", "WFC2D", "WFC2D Plugin"), NAME_None, FWFC2DStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};