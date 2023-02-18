// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Animation/AnimNodeBase.h"
#include "AnimNodes/AnimNode_TwoWayBlend.h"

#include "AnimNode_VictoryTurnInPlace.generated.h"

// Root node of an animation tree (sink)
USTRUCT(BlueprintInternalUseOnly)
struct  FAnimNode_VictoryTurnInPlace : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Links)
	FPoseLink BasePose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links)
	FPoseLink TurnPose;

	//How Quickly to Blend In/Out of Turn Pose
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links,meta = (PinShownByDefault))
	float TurnBlendDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, meta = (PinShownByDefault))
	float TurnSpeedModifierMAX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, meta = (PinShownByDefault))

	float TurnSensitivity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, meta = (PinShownByDefault))

	float MoveSensitivity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, meta = (PinShownByDefault))
	float ShowTurnRotationChangePerTick;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, meta = (PinShownByDefault))
	FVector CurLoc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Links, meta = (PinShownByDefault))
	float CurYaw;

public:	
	FAnimNode_VictoryTurnInPlace();

	// FAnimNode_Base interface
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;
	virtual void Evaluate_AnyThread(FPoseContext& Output) override;
	virtual void GatherDebugData(FNodeDebugData& DebugData) override;
	// End of FAnimNode_Base interface
protected:

	void DeterminUseTurnPose();
	void UpdateBlendAlpha();

protected:
	FAnimNode_TwoWayBlend OurVeryOwnBlend;

	AActor* OwningActor;
	FVector PrevLoc;
	float PrevYaw;
	float TurnAmountThisTick;
	bool WorldIsGame;

	//Blending 

	float BlendDurationMult;
	float InternalBlendDuration;
	float BlendAlpha;
	bool BlendingIntoTurnPose;
	FVector2D RangeIn;
	FVector2D RangeOut;
};
