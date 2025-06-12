// Dmytro Chesniuk All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "SlashEnumTypes.h"

class FSlashCountDownAction : public FPendingLatentAction
{
public:
	FSlashCountDownAction(float InTotalCountDownTime, float InUpdateInterval, float& InOutRemainingTime, ESlashCountDownActionOutput& InCountDownOutput, const FLatentActionInfo& LatentInfo)
		: bNeedToCancel(false),
	TotalCountDownTime(InTotalCountDownTime),
	UpdateInterval(InUpdateInterval),
	OutRemainingTime(InOutRemainingTime),
	CountDownOutput(InCountDownOutput),
	ExecutionFunction(LatentInfo.ExecutionFunction),
	OutputLink(LatentInfo.Linkage),
	CallbackTarget(LatentInfo.CallbackTarget),
	ElapsedInterval(0.f),
	ElapsedTimeSinceStart(0.f){}

	void CancelAction();
	virtual void UpdateOperation(FLatentResponse& Response) override;

private:
	bool bNeedToCancel;
	float TotalCountDownTime;
	float UpdateInterval;
	float& OutRemainingTime;
	ESlashCountDownActionOutput& CountDownOutput;
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	float ElapsedInterval;
	float ElapsedTimeSinceStart;
};
