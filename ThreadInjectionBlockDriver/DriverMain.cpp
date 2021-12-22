#include <ntddk.h>

#include "Constants.h"
#include "ObjectCallback.h"

DRIVER_UNLOAD driver_unload;

ObjectCallback* cb_handler;


extern "C"
NTSTATUS DriverEntry(PDRIVER_OBJECT driver_object, PUNICODE_STRING)
{
	__try
	{
		cb_handler = new ObjectCallback();
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return STATUS_FAILED_DRIVER_ENTRY;
	}

	driver_object->DriverUnload = driver_unload;

	KdPrint(("%s Driver Loaded\n", constants::DRIVER_PREFIX));

	return STATUS_SUCCESS;
}

void driver_unload(PDRIVER_OBJECT)
{
	delete cb_handler;
	KdPrint(("%s Driver Unloaded\n", constants::DRIVER_PREFIX));
}