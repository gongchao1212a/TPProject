// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnimGraphNode_VictoryTurnInPlace.h"
#include "GraphEditorSettings.h"

UAnimGraphNode_VictoryTurnInPlace::UAnimGraphNode_VictoryTurnInPlace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}



FLinearColor UAnimGraphNode_VictoryTurnInPlace::GetNodeTitleColor() const
{
	return FLinearColor(0, 12, 12, 1);
}

FString UAnimGraphNode_VictoryTurnInPlace::GetNodeCategory() const
{
	return FString("Victory Anim Nodes");
}
