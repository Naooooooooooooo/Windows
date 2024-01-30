#include <Windows.h>
#include <tlhelp32.h>
#include <tchar.h>





int main()
{
	DWORD id;
	HANDLE hsnapshot;
	MODULEENTRY32 module_entry;

	wprintf(L"Start listing modules\n");

	id = GetCurrentProcessId();
	wprintf(L"Current process id: %d\n", id);

	wprintf(L"Creating snapshot\n");
	hsnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, id);
	if (!hsnapshot)
	{
		wprintf(L"Creating snapshot failed\n");
		exit(-1);
	}

	wprintf(L"Get the first module\n");

	/*
	* dwSize
	The size of the structure, in bytes. Before calling the Module32First function,
	set this member to sizeof(MODULEENTRY32). If you do not initialize dwSize, 
	Module32First fails.
	*/
	module_entry.dwSize = sizeof(MODULEENTRY32);
	if (!Module32First(hsnapshot, &module_entry))
	{
		wprintf(L"Get the first module failed\n");
		exit(-1);
	}

	wprintf(L"Iterating all modules\n");
	do
	{
		wprintf(L"Module name: %s\n", module_entry.szExePath);
		wprintf(L"Base address: %p\n", module_entry.modBaseAddr);
	} while (Module32Next(hsnapshot, &module_entry));

	CloseHandle(hsnapshot);
	return 0;
}

