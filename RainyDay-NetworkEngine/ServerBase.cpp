#include "stdafx.h"
#include "ServerBase.h"
#include <iostream>


ServerBase::ServerBase(int port)
{
	m_socket = CreateSocket(WSA_FLAG_REGISTERED_IO);

	/// bind
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(m_socket, (SOCKADDR*)&serveraddr, sizeof(serveraddr));

	InitializeRIO();

	m_completionQueue = m_rio.RIOCreateCompletionQueue(RIO_PENDING_RECVS, 0);

	if (m_completionQueue == RIO_INVALID_CQ)
	{
		std::cout << "cq completion fail" << std::endl;
	}
}

void ServerBase::InitializeRIO()
{
	GUID functionTableId = WSAID_MULTIPLE_RIO;

	DWORD dwBytes = 0;

	bool ok = true;

	if (0 != WSAIoctl(
		m_socket,
		SIO_GET_MULTIPLE_EXTENSION_FUNCTION_POINTER,
		&functionTableId,
		sizeof(GUID),
		(void**)&m_rio,
		sizeof(m_rio),
		&dwBytes,
		0,
		0))
	{
		std::cout << "Ioctl fail" << std::endl;
	}
}

SOCKET ServerBase::CreateSocket(const DWORD flags = 0)
{
	m_socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, flags);

	if (m_socket == INVALID_SOCKET)
	{
		return NULL;
	}

	return m_socket
}


ServerBase::~ServerBase()
{
}
