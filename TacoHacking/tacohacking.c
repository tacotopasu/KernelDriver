#pragma warning (disable: 4100 4047 4024)
#include "tacohacking.h"
#include "communication.h"
#include "data.h"
#include "messages.h"
#include "events.h"

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
	UNREFERENCED_PARAMETER(pRegistryPath);
	pDriverObject->DriverUnload = UnloadDriver;
	DbgPrintEx(0, 0, "TACO KERNEL DRIVER // Hello World! Driver output using DbgPrintEx()!");
	DebugMessage("TACO KERNEL DRIVER // Hello World! Driver output using DebugMessage()!");
	
	PsSetLoadImageNotifyRoutine(ImageLoadCallback);
	RtlInitUnicodeString(&dev, L"\\Device\\tacohacking");
	RtlInitUnicodeString(&dos, L"\\DosDevices\\tacohacking");

	IoCreateDevice(pDriverObject, 0, &dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);
	IoCreateSymbolicLink(&dos, &dev);
	pDriverObject->MajorFunction[IRP_MJ_CREATE] = CreateCall;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = CloseCall;
	pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IoControl;

	pDeviceObject->Flags |= DO_DIRECT_IO;
	pDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;
	return STATUS_SUCCESS;
}

NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject)
{
	DebugMessage("TACO KERNEL DRIVER //	Driver-chan says goodbye~");
	PsRemoveLoadImageNotifyRoutine(ImageLoadCallback);
	IoDeleteSymbolicLink(&dos);
	IoDeleteDevice(pDriverObject->DeviceObject);
	return STATUS_SUCCESS;
}