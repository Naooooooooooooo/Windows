* [Link](https://learn.microsoft.com/en-us/windows/win32/toolhelp/traversing-the-module-list)
* First we create a snapshot of current process using `TH32CS_SNAPMODULE` flag.
* Get the current process id using `GetCurrentProcessId` function

```cpp=
id = GetCurrentProcessId();
hsnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, id);
	if (!hsnapshot)
	{
		wprintf(L"Creating snapshot failed\n");
		exit(-1);
	}
```

* Next we get the first module using `Module32First` function
* Notice that we must set `module_entry.dwize = sizeof(MODULEENTRY32)` so that the function can work

```cpp=
module_entry.dwSize = sizeof(MODULEENTRY32);
	if (!Module32First(hsnapshot, &module_entry))
	{
		wprintf(L"Get the first module failed\n");
		exit(-1);
	}
```
* Next we just need to call `Module32Next` to iterate all modules

```cpp=
wprintf(L"Iterating all modules\n");
	do
	{
		wprintf(L"Module name: %s\n", module_entry.szExePath);
		wprintf(L"Base address: %p\n", module_entry.modBaseAddr);
	} while (Module32Next(hsnapshot, &module_entry));
```

![Screenshot 2024-01-30 210307](https://hackmd.io/_uploads/BJVoztI9a.png)
