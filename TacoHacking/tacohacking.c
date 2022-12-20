#pragma warning (disable : 4100)

#include "tacohacking.h"
#include "messages.h"

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
	pDriverObject->DriverUnload = UnloadDriver;
	DbgPrintEx(0, 0, "Hello World! Speaking from da driver!");
	DebugMessage("DebugMessage() works!");
	
	return STATUS_SUCCESS;
}

NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject) {
	DebugMessage("Driver-chan says goodbye~");
	return STATUS_SUCCESS;
}