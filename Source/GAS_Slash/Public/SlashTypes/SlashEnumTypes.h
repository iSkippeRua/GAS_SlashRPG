#pragma once

UENUM()
enum class ESlashConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class ESlashValidType : uint8
{
	Valid,
	Invalid
};

UENUM()
enum class ESlashSuccessTypes : uint8
{
	Successful,
	Failed
};

UENUM()
enum class ESlashCountDownActionInput : uint8
{
	Start,
	Cancel
};

UENUM()
enum class ESlashCountDownActionOutput : uint8
{
	Updated,
	Completed,
	Canceled
};

UENUM(BlueprintType)
enum class ESlashGameDifficulty : uint8
{
	Easy,
	Normal,
	Hard,
	Hardcore
};