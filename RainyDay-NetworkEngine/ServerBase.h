#pragma once
#include <Mswsock.h>
#include <Windows.h>
#include <Winsock2.h>

class ServerBase
{
public:
	ServerBase(int port);
	void InitializeRIO();
	~ServerBase();

private:
	SOCKET CreateSocket(const DWORD flags);

public:

private:

	RIO_EXTENSION_FUNCTION_TABLE m_rio;
	RIO_CQ m_completionQueue;
	RIO_RQ m_requestQueue;

	HANDLE m_hIOCP = nullptr;

	HANDLE m_hStartedEvent = nullptr;
	HANDLE m_hStoppedEvent = nullptr;

	HANDLE m_hReadsToProcessEvent = nullptr;
	HANDLE m_hShutdownReaderThreadEvent = nullptr;

	SOCKET m_socket;
};

