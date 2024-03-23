#pragma once
#include "../../../../../../Source/FactoryGame/Public/Buildables/FGBuildablePipeHyperBooster.h"
#include "IBBuildablePipeHyperBooster.generated.h"

USTRUCT(BlueprintType)
struct INLINEBOOSTERS_API FIBPipeHyperData : public FFGPipeHyperBasePipeData
{
	GENERATED_BODY()

	FIBPipeHyperData(UFGPipeConnectionComponentBase* ExitConn) : FFGPipeHyperBasePipeData(), ExitConnection(ExitConn) {}
	FIBPipeHyperData() : FIBPipeHyperData(nullptr) {}

	UPROPERTY()
	UFGPipeConnectionComponentBase* ExitConnection;

	UPROPERTY()
	bool BoostApplied = false;
};

UCLASS( )
class INLINEBOOSTERS_API AIBBuildablePipeHyperBooster : public AFGBuildablePipeHyperAttachment, public IFGPipeHyperInterface
{
	GENERATED_BODY()
public:
	AIBBuildablePipeHyperBooster();

	//Begin IFGPipeHyperInterface interface
	virtual TArray<TPair<UFGPipeConnectionComponentBase*, float>> GetPossibleConnectionsToTransitionThrough(AFGCharacterPlayer* charPlayer, UFGPipeConnectionComponentBase* connectionEnteredThrough) const override;
	virtual EPipeHyperEnterResult OnPipeEnterReal( AFGCharacterPlayer* charPlayer, UFGPipeConnectionComponentBase* connectionEnteredThrough, TStructOnScope<FFGPipeHyperBasePipeData>& outPipeData, const TStructOnScope<FFGPipeHyperBasePipeData>& predictionPipeData ) override;
	virtual bool FindDistanceClosestToWorldLocation( AFGCharacterPlayer* charPlayer, const FVector& worldLocation, const FVector& velocity, TStructOnScope<FFGPipeHyperBasePipeData>& out_pipeData, float& out_distance ) const override;
	virtual float GetLengthAlongPipe( AFGCharacterPlayer* charPlayer, const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData ) override;
	virtual void GetLocationAndRotationAlongPipe( AFGCharacterPlayer* charPlayer, const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData, float distance, FVector& outLocation, FVector& outDirection ) override;
	virtual UFGPipeConnectionComponentBase* GetConnectionToTransitThrough( AFGCharacterPlayer* charPlayer, const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData, float distance, float& outExitOffset ) override;
	virtual void OnPipeExitReal( AFGCharacterPlayer* charPlayer, TStructOnScope<FFGPipeHyperBasePipeData>& pipeData ) override;
	virtual void OnPipeMoveStep(AFGCharacterPlayer* charPlayer, const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData, float stepLength, const FPlayerPipeHyperData& pipeTravelData, float& pipeVelocityReal, float& pipeTempMinSpeed) override;
	//End IFGPipeHyperInterface interface
protected:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Pipe Hyper" )
	float ActivePowerConsumption;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Pipe Hyper" )
	float PipeVelocityBoostImpulse;
};
