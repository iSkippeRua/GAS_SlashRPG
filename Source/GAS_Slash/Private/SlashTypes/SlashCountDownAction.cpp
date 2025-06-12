// Dmytro Chesniuk All Rights Reserved

#include "SlashTypes/SlashCountDownAction.h"

void FSlashCountDownAction::CancelAction()
{
	bNeedToCancel = true;
}

void FSlashCountDownAction::UpdateOperation(FLatentResponse& Response)
{
	if(bNeedToCancel)
	{
		CountDownOutput = ESlashCountDownActionOutput::Canceled;

		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);

		return;
	}

	if(ElapsedTimeSinceStart >= TotalCountDownTime)
	{
		CountDownOutput = ESlashCountDownActionOutput::Completed;

		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);

		return;
	}

	if(ElapsedInterval < UpdateInterval)
	{
		ElapsedInterval += Response.ElapsedTime();
	} else
	{
		ElapsedTimeSinceStart += UpdateInterval > 0.f ? UpdateInterval : Response.ElapsedTime();

		OutRemainingTime = TotalCountDownTime - ElapsedTimeSinceStart;

		CountDownOutput = ESlashCountDownActionOutput::Updated;
		
		Response.TriggerLink(ExecutionFunction, OutputLink, CallbackTarget);

		ElapsedInterval = 0.f;
	}
}
