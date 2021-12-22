#pragma once
#include <ntddk.h>

extern "C"
NTKERNELAPI BOOLEAN PsIsProcessBeingDebugged(PEPROCESS Process);


class ObjectCallback
{
public:
	ObjectCallback();
	~ObjectCallback();

private:
	PVOID reg_handle_;

	static OB_PREOP_CALLBACK_STATUS on_pre_process_create(PVOID RegistrationContext, POB_PRE_OPERATION_INFORMATION Info);
};

