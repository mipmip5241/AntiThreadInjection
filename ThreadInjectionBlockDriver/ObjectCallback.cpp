#include "ObjectCallback.h"
#include "Constants.h"

ObjectCallback::ObjectCallback() : reg_handle_(nullptr)
{
	OB_OPERATION_REGISTRATION operations[] = {
		{
			PsProcessType,
			OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE,
			on_pre_process_create,
			nullptr
		}
	};

	OB_CALLBACK_REGISTRATION reg = {
		OB_FLT_REGISTRATION_VERSION,
		1,				// operation count
		RTL_CONSTANT_STRING(OBJECT_CALLBACK_ALT),		// altitude
		nullptr,		// context
		operations
	};

	const auto status = ObRegisterCallbacks(&reg, &this->reg_handle_);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("%s Object callback register fail (status=%08X)\n", constants::DRIVER_PREFIX, status));
		ExRaiseStatus(status);
	}
}

ObjectCallback::~ObjectCallback()
{
	ObUnRegisterCallbacks(this->reg_handle_);
}

OB_PREOP_CALLBACK_STATUS ObjectCallback::on_pre_process_create(PVOID, POB_PRE_OPERATION_INFORMATION info)
{
	/* Checking if kernel op */
	if (!info->KernelHandle)
	{
		switch(info->Operation)
		{
			case OB_OPERATION_HANDLE_CREATE:
				if (PsGetCurrentProcessId() != PsGetProcessId(static_cast<PEPROCESS>(info->Object)))
				{
					if(!PsIsProcessBeingDebugged(static_cast<PEPROCESS>(info->Object)))
					{
						info->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_CREATE_THREAD;
					}
				}
				break;

			case OB_OPERATION_HANDLE_DUPLICATE:
				if (!PsIsProcessBeingDebugged(static_cast<PEPROCESS>(info->Parameters->DuplicateHandleInformation.TargetProcess)))
				{
					info->Parameters->DuplicateHandleInformation.DesiredAccess &= ~PROCESS_CREATE_THREAD;
				}
				break;

			default:
				break;
		}

	}
		


	return OB_PREOP_SUCCESS;
}
