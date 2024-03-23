#include "Buildables/IBBuildablePipeHyperBooster.h"

#include "FGPowerInfoComponent.h"
#include "InlineBoosters.h"


AIBBuildablePipeHyperBooster::AIBBuildablePipeHyperBooster(): ActivePowerConsumption(0), PipeVelocityBoostImpulse(0)
{
}

TArray<TPair<UFGPipeConnectionComponentBase*, float>> AIBBuildablePipeHyperBooster::
GetPossibleConnectionsToTransitionThrough(AFGCharacterPlayer* charPlayer,
                                          UFGPipeConnectionComponentBase* connectionEnteredThrough) const
{
	TArray<TPair<UFGPipeConnectionComponentBase*, float>> Array;
	Array.Empty();
	return Array;
}

EPipeHyperEnterResult AIBBuildablePipeHyperBooster::OnPipeEnterReal(AFGCharacterPlayer* charPlayer,
                                                                    UFGPipeConnectionComponentBase*
                                                                    connectionEnteredThrough,
                                                                    TStructOnScope<FFGPipeHyperBasePipeData>&
                                                                    outPipeData,
                                                                    const TStructOnScope<FFGPipeHyperBasePipeData>&
                                                                    predictionPipeData)
{
	// UE_LOG(LogInlineBoosters, Display, TEXT("[Booster] PipeEnterReal"));

	UFGPipeConnectionComponentBase* ExitConnection;
	if (connectionEnteredThrough == GetConnection0())
	{
		ExitConnection = GetConnection1();
	}
	else
	{
		ExitConnection = GetConnection0();
	}

	FIBPipeHyperData Data = FIBPipeHyperData(ExitConnection);
	outPipeData = MakeStructOnScope<FFGPipeHyperBasePipeData, FIBPipeHyperData>(Data);

	return EPipeHyperEnterResult::PHR_Success;
}

bool AIBBuildablePipeHyperBooster::FindDistanceClosestToWorldLocation(AFGCharacterPlayer* charPlayer,
                                                                      const FVector& worldLocation,
                                                                      const FVector& velocity,
                                                                      TStructOnScope<FFGPipeHyperBasePipeData>&
                                                                      out_pipeData,
                                                                      float& out_distance) const
{
	return false;
}

float AIBBuildablePipeHyperBooster::GetLengthAlongPipe(AFGCharacterPlayer* charPlayer,
                                                       const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData)
{
	return 0;
}

void AIBBuildablePipeHyperBooster::GetLocationAndRotationAlongPipe(AFGCharacterPlayer* charPlayer,
                                                                   const TStructOnScope<FFGPipeHyperBasePipeData>&
                                                                   pipeData, float distance, FVector& outLocation,
                                                                   FVector& outDirection)
{
}

UFGPipeConnectionComponentBase* AIBBuildablePipeHyperBooster::GetConnectionToTransitThrough(
	AFGCharacterPlayer* charPlayer, const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData, float distance,
	float& outExitOffset)
{
	return pipeData.CastChecked<FIBPipeHyperData>()->ExitConnection;
}

void AIBBuildablePipeHyperBooster::OnPipeMoveStep(AFGCharacterPlayer* charPlayer,
                                                  const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData,
                                                  float stepLength,
                                                  const FPlayerPipeHyperData& pipeTravelData, float& pipeVelocityReal,
                                                  float& pipeTempMinSpeed)
{
	UE_LOG(LogInlineBoosters, Display, TEXT("[Booster] PipeMoveStep - MinSpeed (%f) Velocty(%f) StepLength(%f)"), pipeTempMinSpeed, pipeVelocityReal, stepLength);
	FVector Direction = pipeTravelData.mPipeDirectionReal;
	UE_LOG(LogInlineBoosters, Display, TEXT("[Booster] Direction of travel: [%f, %f, %f]"), Direction.X, Direction.Y, Direction.Z);

	FIBPipeHyperData* Data = const_cast<FIBPipeHyperData*>(pipeData.CastChecked<FIBPipeHyperData>());

	if (!Data->BoostApplied)
	{
		if (this->mPowerInfo->HasPower())
		{
			const float previousPipeVelocityReal = pipeVelocityReal;
			pipeVelocityReal -= this->PipeVelocityBoostImpulse;
			UE_LOG(LogInlineBoosters, Display, TEXT("[Booster] Boost applied. Speed %f -> %f"), previousPipeVelocityReal, pipeVelocityReal);
		}
		else
		{
			UE_LOG(LogInlineBoosters, Display, TEXT("[Booster] No power. Boost Skipped"));
		}

		Data->BoostApplied = true;
	}
	else
	{
		UE_LOG(LogInlineBoosters, Display, TEXT("[Booster] Boost already applied!"));
	}
}

void AIBBuildablePipeHyperBooster::OnPipeExitReal(AFGCharacterPlayer* charPlayer,
                                                  TStructOnScope<FFGPipeHyperBasePipeData>& pipeData)
{
	// UE_LOG(LogInlineBoosters, Display, TEXT("[Booster] PipeExitReal"));
}
