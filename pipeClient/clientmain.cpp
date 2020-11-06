/* Copyright (C) 2020 Sai Manasa S
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Description: This is a program used to demo use of WIN32 APIs
 * for a basic server-client pipe communication. This file is for
 * the client side of pipe communication.
 * Revision History:
 * Initial version #1: Nov 6th, 2020
 */

#include <iostream>
#include <windows.h>

using namespace std;

void readFromPipe()
{
	HANDLE hPipeClient;
	char rBuffer[1024];
	DWORD dwRead;
	BOOL readSuccessFlag = 0;

	//Connect to the server pipe: \\.\\pipe\\Agentpipe
/*
HANDLE CreateFileA(
  LPCSTR                lpFileName,
  DWORD                 dwDesiredAccess,
  DWORD                 dwShareMode,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  DWORD                 dwCreationDisposition,
  DWORD                 dwFlagsAndAttributes,
  HANDLE                hTemplateFile
);
*/
	cout << "Inside readFromPipe()." << endl;

	hPipeClient = CreateFile(
		TEXT("\\\\.\\pipe\\Agentpipe"), //lpFileName
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		NULL,
		NULL
	);

	/*
	* BOOL ReadFile(
	  HANDLE       hFile,
	  LPVOID       lpBuffer,
	  DWORD        nNumberOfBytesToRead,
	  LPDWORD      lpNumberOfBytesRead,
	  LPOVERLAPPED lpOverlapped
	);
	*/
	while (hPipeClient != INVALID_HANDLE_VALUE)
	{
		cout << "Just connecting to pipe" << endl;
		readSuccessFlag = ReadFile(
			hPipeClient, //HANDLE       hFile,
			rBuffer,     //LPVOID       lpBuffer,
			30,          //DWORD        nNumberOfBytesToRead,
			&dwRead,     //LPDWORD      lpNumberOfBytesRead,
			NULL         //LPOVERLAPPED lpOverlapped
		);

		if (readSuccessFlag)
		{
			cout << "Client has read from pipe of Agent!" << endl;
			cout << "From Agent Pipe: " << rBuffer << endl;
		}
		else
		{
			cout << "Unsuccessful Pipe read!" << endl;
		}
	}
	if(hPipeClient == INVALID_HANDLE_VALUE)
	{
	    cout << "Unsuccesful pipe connection at client end. hPipeClient: " << hPipeClient << endl;
	}
}

int main()
{
	cout << "Inside the client. Calling readFromPipe()" << endl;
	readFromPipe();
	while (1);
	return 0;
}