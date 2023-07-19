#include <new>
#include "client.h"
#include "main.h"

char m_DesiredName[MAX_NAME_LENGTH];

static CClient *CreateClient()
{
	CClient *pClient = static_cast<CClient *>(mem_alloc(sizeof(CClient), 1));
	mem_zero(pClient, sizeof(CClient));
	return new(pClient) CClient;
}

int main(int argc, const char **argv)
{
	if(secure_random_init() != 0)
	{
		dbg_msg("secure", "could not initialize secure RNG");
		return -1;
	}

	CClient *pClient = CreateClient();
	IKernel *pKernel = IKernel::Create();
	pKernel->RegisterInterface(pClient);
	pClient->RegisterInterfaces();

	IEngine *pEngine = CreateEngine("Teeworlds");
	pEngine->Init();
	pClient->InitInterfaces();

	if (argc < 2)
	{
		dbg_msg("chatonly", "usage: chatonly <ip address> [player name]");
		return 0;
	}

	str_copy(pClient->m_aCmdConnect, argv[1], sizeof(pClient->m_aCmdConnect));
	str_copy(m_DesiredName, (argc > 2) ? argv[2] : "chatonly", MAX_NAME_LENGTH);
	pClient->Run();

	return 0;
}