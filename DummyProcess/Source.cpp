#include <iostream>
#include <Windows.h>

int main()
{
	while(true)
	{
		std::cout << GetCurrentProcessId() << std::endl;
	}
}
