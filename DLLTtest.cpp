// DLLTtest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "helloworld.h"
#include <Windows.h>
#include <tchar.h>
#include <libloaderapi.h>
#include <wchar.h>


typedef GoString(__stdcall* CallingGo)();

int main()
{

    HMODULE hDll = LoadLibrary(_T("helloworld"));
	if (!hDll || hDll == INVALID_HANDLE_VALUE) {
		_tprintf(_T("unable to load library"));
		return 1;
	}
	
	CallingGo HelloWorld = (CallingGo)GetProcAddress(hDll, "HelloWorld");
	if (!HelloWorld) {
		MessageBoxA(0, "could not locate the function", "HelloWorld", 0);
		return EXIT_FAILURE;
	}

	GoString HelloReturn = HelloWorld();


	/* Go strings are not NULL terminated*/

	char* cHelloString = (char*)malloc(HelloReturn.n + 1);
	if (!cHelloString) {
		FreeLibrary(hDll);
		return EXIT_FAILURE;
	}
	memcpy(cHelloString, HelloReturn.p, HelloReturn.n);
	cHelloString[HelloReturn.n] = '\0';

	printf("Message from DLL: %s\n", cHelloString);

	free(cHelloString);
	FreeLibrary(hDll);
}

