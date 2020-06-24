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
#include "dep/common/Platform.h"

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

//ÊØ»¤½ø³Ì
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

#if NF_PLATFORM == NF_PLATFORM_WIN
bool ApplicationCtrlHandler(DWORD fdwctrltype)
{
    switch (fdwctrltype)
    {
    case CTRL_C_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
    {
        //bExitApp = true;
    }
    return true;
    default:
        return false;
    }
}
#endif

void CloseXButton()
{
#if NF_PLATFORM == NF_PLATFORM_WIN
    HWND hWnd = GetConsoleWindow();
    if (hWnd)
    {
        HMENU hMenu = GetSystemMenu(hWnd, FALSE);
        EnableMenuItem(hMenu, SC_CLOSE, MF_DISABLED | MF_BYCOMMAND);
    }
#endif
}

void ProcessParameter(int argc, char* argv[])
{
    for (int i = 0; i < argc; i++)
    {
        strArgvList += " ";
        strArgvList += argv[i];
    }

#if NF_PLATFORM == NF_PLATFORM_WIN
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)ApplicationCtrlHandler, true);

    if (strArgvList.find("-x") != string::npos)
    {
        CloseXButton();
    }
#else
    //run it as a daemon process
    if (strArgvList.find("-d") != string::npos)
    {
        InitDaemon();
    }

    signal(SIGPIPE, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);
#endif

    if (strArgvList.find("Path=") != string::npos)
    {
        for (int i = 0; i < argc; i++)
        {
            strDataPath = argv[i];
            if (strDataPath.find("Path=") != string::npos)
            {
                strDataPath.erase(0, 5);
                break;
            }
        }

        g_PluginManger.SetConfigPath(strDataPath);
    }
    else
    {
        g_PluginManger.SetConfigPath("../");
    }

    if (strArgvList.find("Plugin=") != string::npos)
    {
        for (int i = 0; i < argc; i++)
        {
            strPluginName = argv[i];
            if (strPluginName.find(".xml") != string::npos)
            {
                strPluginName.erase(0, 7);
                break;
            }
        }

        g_PluginManger.SetConfigName(strPluginName);
    }

    if (strArgvList.find("Server=") != string::npos)
    {
        for (int i = 0; i < argc; i++)
        {
            strAppName = argv[i];
            if (strAppName.find("Server=") != string::npos)
            {
                strAppName.erase(0, 7);
                break;
            }
        }

        g_PluginManger.SetAppName(strAppName);
    }

    if (strArgvList.find("ID=") != string::npos)
    {
        for (int i = 0; i < argc; i++)
        {
            strAppID = argv[i];
            if (strAppID.find("ID=") != string::npos)
            {
                strAppID.erase(0, 3);
                break;
            }
        }

        int nAppID = 0;
        if (NF_StrTo(strAppID, nAppID))
        {
            g_PluginManger.SetAppID(nAppID);
        }
    }

    if (strArgvList.find("Docker=") != string::npos)
    {
        std::string strDockerFlag = "0";
        for (int i = 0; i < argc; i++)
        {
            strDockerFlag = argv[i];
            if (strDockerFlag.find("Docker=") != string::npos)
            {
                strDockerFlag.erase(0, 7);
                break;
            }
        }

        int nDockerFlag = 0;
        if (NF_StrTo(strDockerFlag, nDockerFlag))
        {
            g_PluginManger.SetRunningDocker(nDockerFlag);
        }
    }

    strTitleName = strAppName + strAppID;// +" PID" + NFGetPID();
    strTitleName.replace(strTitleName.find("Server"), 6, "");
    strTitleName = "NF" + strTitleName;
#if NF_PLATFORM == NF_PLATFORM_WIN
    SetConsoleTitle(strTitleName.c_str());
#elif NF_PLATFORM == NF_PLATFORM_LINUX
    prctl(PR_SET_NAME, strTitleName.c_str());
    //setproctitle(strTitleName.c_str());
#endif
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
