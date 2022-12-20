#pragma warning (disable: 4047)
#include "events.h"
#include "messages.h"
#include "data.h"

PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo)
{
	// DebugMessage("TACO KERNEL DRIVER // Image Loaded: %ls \n", FullImageName->Buffer);

	if (wcsstr(FullImageName->Buffer, L"\\VRChat\\UnityPlayer.dll"))
	{
		DebugMessage("TACO KERNEL DRIVER // VRChat UnityPlayer.dll found!\n");
		VRChatClientDLLAdress = ImageInfo->ImageBase;

		DebugMessage("TACO KERNEL DRIVER // VRChat Process ID: %d \n", ProcessId);
	}

	return STATUS_SUCCESS;
}