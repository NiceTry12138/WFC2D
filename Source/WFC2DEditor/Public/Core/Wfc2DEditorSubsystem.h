// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "Wfc2DEditorSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class WFC2DEDITOR_API UWfc2DEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()
	
public:
	int GetTileIndex();

private:
	int Index{0};

};
