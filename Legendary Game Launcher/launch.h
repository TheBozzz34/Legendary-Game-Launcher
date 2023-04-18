#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include <codecvt>
#include <locale>

int launch(std::string id)
{
	std::string command = "C:\\Users\\sansm\\bin\\legendary.exe launch " + id;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wstr = converter.from_bytes(command);
	STARTUPINFOW si = { 0 };
	si.cb = sizeof(STARTUPINFOW);
	PROCESS_INFORMATION pi = { 0 };
	BOOL success = CreateProcessW(NULL, const_cast<wchar_t*>(wstr.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	if (!success) {
		std::cerr << "Failed to start process. Error code: " << GetLastError() << std::endl;
		system("pause");
		return 1;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	DWORD exitCode = 0;
	if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
		std::cerr << "Failed to get process exit code. Error code: " << GetLastError() << std::endl;
		system("pause");
	}
	else {
		std::cout << "Process exited with code " << exitCode << std::endl;
	}
}