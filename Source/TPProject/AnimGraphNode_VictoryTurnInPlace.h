// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "AnimNode_VictoryTurnInPlace.h"
#include "AnimGraphNode_Base.h"
#include "AnimGraphNode_VictoryTurnInPlace.generated.h"

class FBlueprintActionDatabaseRegistrar;

UCLASS(MinimalAPI)
class UAnimGraphNode_VictoryTurnInPlace : public UAnimGraphNode_Base
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category=Settings)
	FAnimNode_VictoryTurnInPlace Node;

public:
	// UEdGraphNode interface
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FString GetNodeCategory() const override;
	// End of UEdGraphNode interface

};
