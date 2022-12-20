#pragma warning (disable: 4100 4047 4024)
#include "tacohacking.h"
#include "messages.h"
#include "events.h"

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
	UNREFERENCED_PARAMETER(pRegistryPath);
	pDriverObject->DriverUnload = UnloadDriver;
	DbgPrintEx(0, 0, "TACO KERNEL DRIVER // Hello World! Driver output using DbgPrintEx()!");
	DebugMessage("TACO KERNEL DRIVER // Hello World! Driver output using DebugMessage()!");
	
	PsSetLoadImageNotifyRoutine(ImageLoadCallback);
	return STATUS_SUCCESS;
}

NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject)
{
	DebugMessage("TACO KERNEL DRIVER //  Driver-chan says goodbye~");
	PsRemoveLoadImageNotifyRoutine(ImageLoadCallback);
	return STATUS_SUCCESS;
}