// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnimNode_VictoryTurnInPlace.h"

FAnimNode_VictoryTurnInPlace::FAnimNode_VictoryTurnInPlace()
	:FAnimNode_Base()
	,TurnBlendDuration(4.f)
	,TurnSpeedModifierMAX(4.333)
	,TurnSensitivity(0.777f)
	,MoveSensitivity(25.f)
{
	WorldIsGame = false;
	BlendDurationMult = 1.0f;
	InternalBlendDuration = TurnBlendDuration / 100;
	RangeIn = FVector2D(0, TurnSpeedModifierMAX);
	RangeOut = FVector2D(0, 1);
	ShowTurnRotationChangePerTick = false;
	CurYaw = 0.0f;
	CurLoc = FVector::ZeroVector;
}

void FAnimNode_VictoryTurnInPlace::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	BasePose.Initialize(Context);
	TurnPose.Initialize(Context);

	OurVeryOwnBlend.A = BasePose;
	OurVeryOwnBlend.B = TurnPose;
	OurVeryOwnBlend.Initialize_AnyThread(Context);

}

void FAnimNode_VictoryTurnInPlace::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	BasePose.CacheBones(Context);
	TurnPose.CacheBones(Context);
}

void FAnimNode_VictoryTurnInPlace::Update_AnyThread(const FAnimationUpdateContext& Context)
{

	DeterminUseTurnPose();
	UpdateBlendAlpha();

	if (BlendAlpha >= 1)
	{
		TurnPose.Update(Context);
	}
	else if (BlendAlpha <= 0)
	{
		BasePose.Update(Context);
	}
	else
	{
		OurVeryOwnBlend.Alpha = BlendAlpha;
		OurVeryOwnBlend.Update_AnyThread(Context);
	}

}

void FAnimNode_VictoryTurnInPlace::Evaluate_AnyThread(FPoseContext& Output)
{
	if (BlendAlpha <= 0)
	{
		BasePose.Evaluate(Output);
	}
	else if (BlendAlpha >= 1)
	{
		TurnPose.Evaluate(Output);
	}
	else
	{
		OurVeryOwnBlend.Evaluate_AnyThread(Output);
	}

}

void FAnimNode_VictoryTurnInPlace::GatherDebugData(FNodeDebugData& DebugData)
{
	FString DebugLine = DebugData.GetNodeName(this);
	DebugData.AddDebugItem(DebugLine);
	BasePose.GatherDebugData(DebugData);
	TurnPose.GatherDebugData(DebugData);
}

void FAnimNode_VictoryTurnInPlace::DeterminUseTurnPose()
{
	// Choose Turn Pose or Base Pose
	TurnAmountThisTick = FMath::Abs(CurYaw - PrevYaw);
	if (TurnAmountThisTick < TurnSensitivity)
	{
		BlendingIntoTurnPose = false;
	}

	else if (FVector::DistSquared(CurLoc,PrevLoc) < MoveSensitivity)
	{
		BlendingIntoTurnPose = true;
	}
	
	PrevYaw = CurYaw;
	PrevLoc = CurLoc;
	//Log the Change in Rotation Per Tick
	if (ShowTurnRotationChangePerTick)
	{
		UE_LOG(LogAnimation, Warning, TEXT("turn difference per tick,  %f"), TurnAmountThisTick);
	}
	RangeIn.Y = TurnSpeedModifierMAX;
	BlendDurationMult = FMath::GetMappedRangeValueClamped(RangeIn, RangeOut, TurnAmountThisTick);
}

void FAnimNode_VictoryTurnInPlace::UpdateBlendAlpha()
{
	if (BlendingIntoTurnPose)
	{
		if (BlendAlpha >= 1)
		{
			BlendAlpha = 1;
		}
		else
		{
			//modify blend-in by speed of turning
			BlendAlpha += InternalBlendDuration * BlendDurationMult;
		}
	}
	else
	{
		if (BlendAlpha <= 0)
		{
			BlendAlpha = 0;
		}
		else
		{
			BlendAlpha -= InternalBlendDuration;
		}
	}

}

