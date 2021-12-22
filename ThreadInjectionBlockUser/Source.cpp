#include <iostream>
#include <Windows.h>
#include <processthreadsapi.h>


DWORD WINAPI  foo(_In_ LPVOID lpParameter);
int print_error(const char* msg);

int main()
{
	/*Self thread creation should work*/
	auto handle = GetCurrentProcess();
	auto res = CreateRemoteThread(handle, nullptr, 1024, foo, nullptr, NULL, nullptr);
	if (!res)
		print_error("self thread create fail");

	/* Remote thread creation should fail if driver works*/
	DWORD pid = 0;
	printf("Enter pid: ");
	std::cin >> pid;
	handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	res = CreateRemoteThread(handle, nullptr, 1024, foo, nullptr, NULL, nullptr);

	if (!res)
		print_error("remote thread create fail");

	return 0;
}


DWORD WINAPI  foo(_In_ LPVOID lpParameter)
{
	printf("thread created");

	return 0;
}

int print_error(const char* msg)
{
	printf("%s error code = %lu\n", msg, GetLastError());
	return 1;
}