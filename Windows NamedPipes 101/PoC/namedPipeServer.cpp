#include "pch.h"
#include <Windows.h>
#include <iostream>

int main() {
	LPCWSTR pipeName = L"\\\\.\\pipe\\mantvydas-first-pipe";
	LPVOID pipeBuffer = NULL;
	HANDLE serverPipe;
	DWORD readBytes = 0;
	DWORD readBuffer = 0;
	int err = 0;
	BOOL isPipeConnected;
	BOOL isPipeOpen;
	wchar_t message[] = L"HELL";
	DWORD messageLenght = lstrlen(message) * 2;
	DWORD bytesWritten = 0;

	std::wcout << "Creating named pipe " << pipeName << std::endl;
	serverPipe = CreateNamedPipe(pipeName, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE, 1, 2048, 2048, 0, NULL);
	
	isPipeConnected = ConnectNamedPipe(serverPipe, NULL);
	if (isPipeConnected) {
		std::wcout << "Incoming connection to " << pipeName << std::endl;
	}
	
	std::wcout << "Sending message: " << message << std::endl;
	WriteFile(serverPipe, message, messageLenght, &bytesWritten, NULL);
	
	return 0;
}
