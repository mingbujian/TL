/*
            This file is part of: 
                NoahFrame
            https://github.com/ketoo/NoahGameFrame

   Copyright 2009 - 2019 NoahFrame(NoahGameFrame)

   File creator: lvsheng.huang
   
   NoahFrame is open-source software and you can redistribute it and/or modify
   it under the terms of the License; besides, anyone who use this file/software must include this copyright announcement.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/


#include "NFPluginManager.h"
#include "Dep/RapidXML/rapidxml.hpp"
#include "Dep/RapidXML/rapidxml_iterators.hpp"
#include "Dep/RapidXML/rapidxml_print.hpp"
#include "Dep/RapidXML/rapidxml_utils.hpp"
#include "NFIPlugin.h"
#include "NFPlatform.h"

#if NF_PLATFORM == NF_PLATFORM_WIN
#pragma comment( lib, "ws2_32.lib" )
#endif

#ifdef NF_DEBUG_MODE

#if NF_PLATFORM == NF_PLATFORM_WIN

#elif NF_PLATFORM == NF_PLATFORM_LINUX || NF_PLATFORM == NF_PLATFORM_ANDROID
//#pragma comment( lib, "libtherond.a" )
#elif NF_PLATFORM == NF_PLATFORM_APPLE || NF_PLATFORM == NF_PLATFORM_APPLE_IOS
//#pragma comment( lib, "libtherond.a" )
#endif

#else

#if NF_PLATFORM == NF_PLATFORM_WIN

#elif NF_PLATFORM == NF_PLATFORM_LINUX || NF_PLATFORM == NF_PLATFORM_ANDROID
//#pragma comment( lib, "libtheron.a" )
#elif NF_PLATFORM == NF_PLATFORM_APPLE || NF_PLATFORM == NF_PLATFORM_APPLE_IOS
//#pragma comment( lib, "libtheron.a" )
#endif

#endif


#ifndef NF_DYNAMIC_PLUGIN
//for nf-sdk plugins
//#include "NFComm/NFTestPlugin/NFTestPlugin.h"
#endif

void CoroutineExecute(void* arg)
{
	NFPluginManager::Instance()->Execute();
}

NFPluginManager::NFPluginManager() : NFIPluginManager()
{
	mnAppID = 0;
    mbIsDocker = false;

	mCurrentPlugin = nullptr;

#ifdef NF_DYNAMIC_PLUGIN
	mbStaticPlugin = false;
#else
	mbStaticPlugin = true;
#endif

	mnInitTime = time(NULL);
	mnNowTime = mnInitTime;

	mGetFileContentFunctor = nullptr;

	mstrConfigPath = "../";

#ifdef NF_DEBUG_MODE
   mstrConfigName = "NFDataCfg/Debug/Plugin.xml";
#else
   mstrConfigName = "NFDataCfg/Release/Plugin.xml";
#endif
}

NFPluginManager::~NFPluginManager()
{

}

bool NFPluginManager::LoadPlugin()
{
	std::cout << "----LoadPlugin----" << std::endl;

	LoadPluginConfig();

#ifndef NF_DYNAMIC_PLUGIN
	LoadStaticPlugin();
#endif

	PluginNameMap::iterator it = mPluginNameMap.begin();
	for (; it != mPluginNameMap.end(); ++it)
	{
#ifdef NF_DYNAMIC_PLUGIN
		LoadPluginLibrary(it->first);
#else
		LoadStaticPlugin(it->first);
#endif
	}

#ifndef NF_DYNAMIC_PLUGIN
	CheckStaticPlugin();
#endif

	return true;
}

bool NFPluginManager::Awake()
{
	std::cout << "----Awake----" << std::endl;

	PluginInstanceMap::iterator itAfterInstance = mPluginInstanceMap.begin();
	for (; itAfterInstance != mPluginInstanceMap.end(); itAfterInstance++)
	{
		SetCurrentPlugin(itAfterInstance->second);
		itAfterInstance->second->Awake();
	}

	return true;
}

inline bool NFPluginManager::Init()
{
	std::cout << "----Init----" << std::endl;

	PluginInstanceMap::iterator itInstance = mPluginInstanceMap.begin();
	for (; itInstance != mPluginInstanceMap.end(); itInstance++)
	{
		SetCurrentPlugin(itInstance->second);
		itInstance->second->Init();
	}

	return true;
}

bool NFPluginManager::LoadPluginConfig()
{
	std::string strContent;
	std::string strFilePath = GetConfigPath() + mstrConfigName;
	GetFileContent(strFilePath, strContent);

	rapidxml::xml_document<> xDoc;
	xDoc.parse<0>((char*)strContent.c_str());

    rapidxml::xml_node<>* pRoot = xDoc.first_node();
    rapidxml::xml_node<>* pAppNameNode = pRoot->first_node(mstrAppName.c_str());
    if (!pAppNameNode)
    {
        NFASSERT(0, "There are no App ID", __FILE__, __FUNCTION__);
        return false;
    }

    for (rapidxml::xml_node<>* pPluginNode = pAppNameNode->first_node("Plugin"); pPluginNode; pPluginNode = pPluginNode->next_sibling("Plugin"))
    {
        const char* strPluginName = pPluginNode->first_attribute("Name")->value();

        mPluginNameMap.insert(PluginNameMap::value_type(strPluginName, true));

    }

    return true;
}

bool NFPluginManager::LoadStaticPlugin()
{

#ifndef NF_DYNAMIC_PLUGIN

//for nf-sdk plugins
	//CREATE_PLUGIN(this, TestPlugin)

//DB

//GAME

//LOGIN

//MASTER

//PROXY

//WORLD

//MIDWARE

#endif

    return true;
}

bool NFPluginManager::CheckStaticPlugin()
{
#ifndef NF_DYNAMIC_PLUGIN
	//plugin
	for (auto it = mPluginInstanceMap.begin(); it != mPluginInstanceMap.end();)
	{
		bool bFind = false;
		const std::string& strPluginName = it->first;
		for (int i = 0; i < mStaticPlugin.size(); ++i)
		{
			const std::string& tempPluginName = mStaticPlugin[i];
			if (tempPluginName == strPluginName)
			{
				bFind = true;
			}
		}

		if (!bFind)
		{
			it = mPluginInstanceMap.erase(it);  
		}
		else
		{
			it++;
		}
	}
#endif

    return true;
}

bool NFPluginManager::LoadStaticPlugin(const std::string& strPluginDLLName)
{
	mStaticPlugin.push_back(strPluginDLLName);

	return true;
}

void NFPluginManager::Registered(NFIPlugin* plugin)
{
    const std::string& strPluginName = plugin->GetPluginName();
    if (!FindPlugin(strPluginName))
	{
		mPluginInstanceMap.insert(PluginInstanceMap::value_type(strPluginName, plugin));
        plugin->Install();
    }
	else
	{
		std::cout << strPluginName << std::endl;
		assert(0);
	}
}

void NFPluginManager::UnRegistered(NFIPlugin* plugin)
{
    PluginInstanceMap::iterator it = mPluginInstanceMap.find(plugin->GetPluginName());
    if (it != mPluginInstanceMap.end())
    {
        it->second->Uninstall();
        delete it->second;
        it->second = NULL;
        mPluginInstanceMap.erase(it);
    }
}

bool NFPluginManager::ReLoadPlugin(const std::string & strPluginDLLName)
{
	//1.shut all module of this plugin
	//2.unload this plugin
	//3.load new plugin
	//4.init new module
	//5.tell others who has been reloaded
	PluginInstanceMap::iterator itInstance = mPluginInstanceMap.find(strPluginDLLName);
	if (itInstance == mPluginInstanceMap.end())
	{
		return false;
	}
	//1
	NFIPlugin* pPlugin = itInstance->second;

	//2
	PluginLibMap::iterator it = mPluginLibMap.find(strPluginDLLName);
	if (it != mPluginLibMap.end())
	{
		NFDynLib* pLib = it->second;
		DLL_STOP_PLUGIN_FUNC pFunc = (DLL_STOP_PLUGIN_FUNC)pLib->GetSymbol("DllStopPlugin");

		if (pFunc)
		{
			pFunc(this);
		}

		pLib->UnLoad();

		delete pLib;
		pLib = NULL;
		mPluginLibMap.erase(it);
	}

	//3
	NFDynLib* pLib = new NFDynLib(strPluginDLLName);
	bool bLoad = pLib->Load();
	if (bLoad)
	{
		mPluginLibMap.insert(PluginLibMap::value_type(strPluginDLLName, pLib));

		DLL_START_PLUGIN_FUNC pFunc = (DLL_START_PLUGIN_FUNC)pLib->GetSymbol("DllStartPlugin");
		if (!pFunc)
		{
			std::cout << "Reload Find function DllStartPlugin Failed in [" << pLib->GetName() << "]" << std::endl;
			assert(0);
			return false;
		}

		pFunc(this);
	}
	else
	{
#if NF_PLATFORM == NF_PLATFORM_LINUX
		char* error = dlerror();
		if (error)
		{
			std::cout << stderr << " Reload shared lib[" << pLib->GetName() << "] failed, ErrorNo. = [" << error << "]" << std::endl;
			std::cout << "Reload [" << pLib->GetName() << "] failed" << std::endl;
			assert(0);
			return false;
		}
#elif NF_PLATFORM == NF_PLATFORM_WIN
		std::cout << stderr << " Reload DLL[" << pLib->GetName() << "] failed, ErrorNo. = [" << GetLastError() << "]" << std::endl;
		std::cout << "Reload [" << pLib->GetName() << "] failed" << std::endl;
		assert(0);
		return false;
#endif // NF_PLATFORM
	}

	//4
	PluginInstanceMap::iterator itReloadInstance = mPluginInstanceMap.begin();
	for (; itReloadInstance != mPluginInstanceMap.end(); itReloadInstance++)
	{
		if (strPluginDLLName != itReloadInstance->first)
		{
			itReloadInstance->second->OnReloadPlugin();
		}
	}
	return true;
}

NFIPlugin* NFPluginManager::FindPlugin(const std::string& strPluginName)
{
    PluginInstanceMap::iterator it = mPluginInstanceMap.find(strPluginName);
    if (it != mPluginInstanceMap.end())
    {
        return it->second;
    }

    return NULL;
}

bool NFPluginManager::Execute()
{
    mnNowTime = time(NULL);

    bool bRet = true;

    PluginInstanceMap::iterator it = mPluginInstanceMap.begin();
    for (; it != mPluginInstanceMap.end(); ++it)
    {
        bool tembRet = it->second->Execute();
        bRet = bRet && tembRet;
    }

    return bRet;
}

inline int NFPluginManager::GetAppID() const
{
	return mnAppID;
}

inline void NFPluginManager::SetAppID(const int nAppID)
{
    mnAppID = nAppID;
}

bool NFPluginManager::IsRunningDocker() const
{
	return mbIsDocker;
}

void NFPluginManager::SetRunningDocker(bool bDocker)
{
	mbIsDocker = bDocker;
}

bool NFPluginManager::IsStaticPlugin() const
{
	return mbStaticPlugin;
}

inline NFINT64 NFPluginManager::GetInitTime() const
{
	return mnInitTime;
}

inline NFINT64 NFPluginManager::GetNowTime() const
{
	return mnNowTime;
}

inline const std::string & NFPluginManager::GetConfigPath() const
{
	return mstrConfigPath;
}

inline void NFPluginManager::SetConfigPath(const std::string & strPath)
{
	mstrConfigPath = strPath;
}

void NFPluginManager::SetConfigName(const std::string & strFileName)
{
	if (strFileName.empty())
	{
		return;
	}

	if (strFileName.find(".xml") == string::npos)
	{
		return;
	}

#ifdef NF_DEBUG_MODE
	mstrConfigName = "NFDataCfg/Debug/" + strFileName;
#else
	mstrConfigName = "NFDataCfg/Release/" + strFileName;
#endif
}

const std::string& NFPluginManager::GetConfigName() const
{
	return mstrConfigName;
}

const std::string& NFPluginManager::GetAppName() const
{
	return mstrAppName;
}

void NFPluginManager::SetAppName(const std::string& strAppName)
{
	if (!mstrAppName.empty())
	{
		return;
	}

	mstrAppName = strAppName;
}

const std::string & NFPluginManager::GetLogConfigName() const
{
	return mstrLogConfigName;
}

void NFPluginManager::SetLogConfigName(const std::string & strName)
{
	mstrLogConfigName = strName;
}

void NFPluginManager::SetCurrentPlugin(NFIPlugin* pPlugin)
{
	mCurrentPlugin = pPlugin;
}

NFIPlugin * NFPluginManager::GetCurrentPlugin()
{
	return mCurrentPlugin;
}

void NFPluginManager::SetGetFileContentFunctor(GET_FILECONTENT_FUNCTOR fun)
{
	mGetFileContentFunctor = fun;
}

bool NFPluginManager::GetFileContent(const std::string &strFileName, std::string &strContent)
{
	if (mGetFileContentFunctor)
	{
		return mGetFileContentFunctor(strFileName, strContent);
	}

	FILE *fp = fopen(strFileName.c_str(), "rb");
	if (!fp)
	{
		return false;
	}

	fseek(fp, 0, SEEK_END);
	const long filelength = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	strContent.resize(filelength);
	fread((void*)strContent.data(), filelength, 1, fp);
	fclose(fp);

	return true;
}

bool NFPluginManager::AfterInit()
{
	std::cout << "----AfterInit----" << std::endl;

    PluginInstanceMap::iterator itAfterInstance = mPluginInstanceMap.begin();
    for (; itAfterInstance != mPluginInstanceMap.end(); itAfterInstance++)
    {
		SetCurrentPlugin(itAfterInstance->second);
        itAfterInstance->second->AfterInit();
    }

    return true;
}

bool NFPluginManager::CheckConfig()
{
	std::cout << "----CheckConfig----" << std::endl;

    PluginInstanceMap::iterator itCheckInstance = mPluginInstanceMap.begin();
    for (; itCheckInstance != mPluginInstanceMap.end(); itCheckInstance++)
    {
		SetCurrentPlugin(itCheckInstance->second);
        itCheckInstance->second->CheckConfig();
    }

    return true;
}

bool NFPluginManager::ReadyExecute()
{
	std::cout << "----ReadyExecute----" << std::endl;

    PluginInstanceMap::iterator itCheckInstance = mPluginInstanceMap.begin();
    for (; itCheckInstance != mPluginInstanceMap.end(); itCheckInstance++)
    {
		SetCurrentPlugin(itCheckInstance->second);
        itCheckInstance->second->ReadyExecute();
    }

    return true;
}

bool NFPluginManager::BeforeShut()
{
    PluginInstanceMap::iterator itBeforeInstance = mPluginInstanceMap.begin();
    for (; itBeforeInstance != mPluginInstanceMap.end(); itBeforeInstance++)
    {
		SetCurrentPlugin(itBeforeInstance->second);
        itBeforeInstance->second->BeforeShut();
    }

    return true;
}

bool NFPluginManager::Shut()
{
    PluginInstanceMap::iterator itInstance = mPluginInstanceMap.begin();
    for (; itInstance != mPluginInstanceMap.end(); ++itInstance)
    {
		SetCurrentPlugin(itInstance->second);
        itInstance->second->Shut();
    }

    return true;
}

bool NFPluginManager::Finalize()
{
	PluginInstanceMap::iterator itInstance = mPluginInstanceMap.begin();
	for (; itInstance != mPluginInstanceMap.end(); itInstance++)
	{
		SetCurrentPlugin(itInstance->second);
		itInstance->second->Finalize();
	}

	////////////////////////////////////////////////

	PluginNameMap::iterator it = mPluginNameMap.begin();
	for (; it != mPluginNameMap.end(); it++)
	{
#ifdef NF_DYNAMIC_PLUGIN
		UnLoadPluginLibrary(it->first);
#else
		UnLoadStaticPlugin(it->first);
#endif
	}

	mPluginInstanceMap.clear();
	mPluginNameMap.clear();

	return true;
}

bool NFPluginManager::LoadPluginLibrary(const std::string& strPluginDLLName)
{
    PluginLibMap::iterator it = mPluginLibMap.find(strPluginDLLName);
    if (it == mPluginLibMap.end())
    {
        NFDynLib* pLib = new NFDynLib(strPluginDLLName);
        bool bLoad = pLib->Load();

        if (bLoad)
        {
            mPluginLibMap.insert(PluginLibMap::value_type(strPluginDLLName, pLib));

            DLL_START_PLUGIN_FUNC pFunc = (DLL_START_PLUGIN_FUNC)pLib->GetSymbol("DllStartPlugin");
            if (!pFunc)
            {
                std::cout << "Find function DllStartPlugin Failed in [" << pLib->GetName() << "]" << std::endl;
                assert(0);
                return false;
            }

            pFunc(this);

            return true;
        }
        else
        {
#if NF_PLATFORM == NF_PLATFORM_LINUX || NF_PLATFORM == NF_PLATFORM_APPLE
            char* error = dlerror();
            if (error)
            {
                std::cout << stderr << " Load shared lib[" << pLib->GetName() << "] failed, ErrorNo. = [" << error << "]" << std::endl;
                std::cout << "Load [" << pLib->GetName() << "] failed" << std::endl;
                assert(0);
                return false;
            }
#elif NF_PLATFORM == NF_PLATFORM_WIN
            std::cout << stderr << " Load DLL[" << pLib->GetName() << "] failed, ErrorNo. = [" << GetLastError() << "]" << std::endl;
            std::cout << "Load [" << pLib->GetName() << "] failed" << std::endl;
            assert(0);
            return false;
#endif // NF_PLATFORM
        }
    }

    return false;
}

bool NFPluginManager::UnLoadPluginLibrary(const std::string& strPluginDLLName)
{
    PluginLibMap::iterator it = mPluginLibMap.find(strPluginDLLName);
    if (it != mPluginLibMap.end())
    {
        NFDynLib* pLib = it->second;
        DLL_STOP_PLUGIN_FUNC pFunc = (DLL_STOP_PLUGIN_FUNC)pLib->GetSymbol("DllStopPlugin");

        if (pFunc)
        {
            pFunc(this);
        }

        pLib->UnLoad();

        delete pLib;
        pLib = NULL;
        mPluginLibMap.erase(it);

        return true;
    }

    return false;
}

bool NFPluginManager::UnLoadStaticPlugin(const std::string & strPluginDLLName)
{
	//     DESTROY_PLUGIN(this, NFConfigPlugin)
	//     DESTROY_PLUGIN(this, NFEventProcessPlugin)
	//     DESTROY_PLUGIN(this, NFKernelPlugin)
	return false;
}