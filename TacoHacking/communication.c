#pragma warning(disable: 4022)
#include "communication.h"
#include "messages.h"
#include "memory.h"
#include "data.h"

NTSTATUS CreateCall(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	DebugMessage("TACO KERNEL DRIVER // CreateCall() called.\n");
	DebugMessage("TACO KERNEL DRIVER // Connection estabilished!\n");

	return STATUS_SUCCESS;
}

NTSTATUS CloseCall(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

NTSTATUS IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	NTSTATUS Status = STATUS_UNSUCCESSFUL;
	ULONG ByteIO = 0;

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

	ULONG ControlCode = stack->Parameters.DeviceIoControl.IoControlCode;

	if (ControlCode == IO_GET_CLIENT_ADDRESS)
	{
		PULONG Output = (PULONG)Irp->AssociatedIrp.SystemBuffer;
		*Output = GameClientDLLAddress;

		DebugMessage("TACO KERNEL DRIVER // ClientAddress requested!\n");
		Status = STATUS_SUCCESS;
		ByteIO = sizeof(*Output);
	}
	else if (ControlCode == IO_READ_REQUEST)
	{
		PKERNEL_READ_REQUEST ReadInput = (PKERNEL_READ_REQUEST)Irp->AssociatedIrp.SystemBuffer;
		PEPROCESS Process;
		if (NT_SUCCESS(PsLookupProcessByProcessId(ReadInput->ProcessId, &Process)))
		{
			KernelReadVirtualMemory(Process, ReadInput->Address, ReadInput->pBuff, ReadInput->Size);
			Status = STATUS_SUCCESS;
			ByteIO = sizeof(KERNEL_READ_REQUEST);
		}
	}
	else if (ControlCode == IO_WRITE_REQUEST)
	{
		PKERNEL_WRITE_REQUEST WriteInput = (PKERNEL_WRITE_REQUEST)Irp->AssociatedIrp.SystemBuffer;
		PEPROCESS Process;
		if (NT_SUCCESS(PsLookupProcessByProcessId(WriteInput->ProcessId, &Process)))
		{
			KernelWriteVirtualMemory(Process, WriteInput->pBuff, WriteInput->Address, WriteInput->Size);
			Status = STATUS_SUCCESS;
			ByteIO = sizeof(KERNEL_WRITE_REQUEST);
		}
	}
	else
	{
		ByteIO = 0;
	}

	Irp->IoStatus.Status = Status;
	Irp->IoStatus.Information = ByteIO;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return Status;
}