#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <future>
#include <functional>
#include <atomic>
#include "PluginManager.h"
//#include "NFComm/NFCore/NFException.h"
#include "Platform.h"
//#include "NFComm/NFLogPlugin/easylogging++.h"

#if NF_PLATFORM != NF_PLATFORM_WIN
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <signal.h>
#include <execinfo.h>
#include <setjmp.h>

#if NF_PLATFORM == NF_PLATFORM_LINUX
#include <sys/prctl.h>
#endif

#endif

bool bExitApp = false;
std::thread gThread;
std::string strArgvList;
std::string strPluginName;
std::string strDataPath;
std::string strAppName;
std::string strAppID;
std::string strTitleName;

void ReleaseNF()
{
}

//守护进程
void InitDaemon()
{
#if NF_PLATFORM != NF_PLATFORM_WIN
	daemon(1, 0);

	// ignore signals
	signal(SIGINT, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
#endif
}

void PrintfLogo()
{
	std::cout << "Hello World!" << std::endl;
}


void ProcessParameter(int argc, char* argv[])
{
    //不是调试模式，InitDaemon();
}


int main(int argc, char* argv[])
{
	std::cout << "__cplusplus:" << __cplusplus << std::endl;

#if NF_PLATFORM == NF_PLATFORM_WIN
	//SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
#else
	signal(SIGSEGV, NFCrashHandler);
	//el::Helpers::setCrashHandler(CrashHandler);
#endif

	ProcessParameter(argc, argv);
	PrintfLogo();

    g_PluginManger.LoadPlugin();
	g_PluginManger.Awake();
	g_PluginManger.Init();
	g_PluginManger.AfterInit();
	g_PluginManger.CheckConfig();
	g_PluginManger.ReadyExecute();

    uint64_t nIndex = 0;
    while (!bExitApp)
    {
        nIndex++;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        g_PluginManger.Execute();
    }

	ReleaseNF();

	return 0;
}
