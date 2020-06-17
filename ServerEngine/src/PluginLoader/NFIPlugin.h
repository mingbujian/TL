/*
            This file is part of: 
                NoahFrame
            https://github.com/ketoo/NoahGameFrame

   Copyright 2009 - 2020 NoahFrame(NoahGameFrame)

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


#ifndef NFI_PLUGIN_H
#define NFI_PLUGIN_H

#include <iostream>
#include <assert.h>
#include "NFIPluginManager.h"

#define CREATE_PLUGIN(pManager, className)  NFIPlugin* pCreatePlugin##className = new className(pManager); pManager->Registered( pCreatePlugin##className );

#define DESTROY_PLUGIN(pManager, className) pManager->UnRegistered( pManager->FindPlugin((#className)) );

/*
#define REGISTER_COMPONENT(pManager, className)  NFIComponent* pRegisterComponent##className= new className(pManager); \
    pRegisterComponent##className->strName = (#className); \
    pManager->AddComponent( (#className), pRegisterComponent##className );

#define UNREGISTER_COMPONENT(pManager, className) NFIComponent* pRegisterComponent##className =  \
        dynamic_cast<NFIComponent*>( pManager->FindComponent( (#className) ) ); pManager->RemoveComponent( (#className) ); delete pRegisterComponent##className;
*/

class NFIPluginManager;

class NFIPlugin
{

public:
	NFIPlugin(NFIPluginManager* p) : pPluginManager(p)
	{
	}
    virtual ~NFIPlugin()
	{
	}
    virtual const int GetPluginVersion() = 0;
    virtual const std::string GetPluginName() = 0;

    virtual void Install() = 0;

	virtual void Uninstall() = 0;

	virtual bool Awake()
	{

		return true;
	}

    virtual bool Init()
	{
        return true;
    }

    virtual bool AfterInit()
    {
        return true;
    }

    virtual bool CheckConfig()
    {
        return true;
    }

	virtual bool ReadyExecute()
	{
		return true;
	}

    virtual bool Execute()
    {
        return true;
    }

    virtual bool BeforeShut()
    {
        return true;
    }

    virtual bool Shut()
    {
        return true;
    }

    virtual bool Finalize()
	{
        return true;
    }

	virtual bool OnReloadPlugin()
	{
		return true;
	}

	virtual NFIPluginManager* GetPluginManager() const
	{
		return pPluginManager;
	}
protected:
	NFIPluginManager* pPluginManager = NULL;
};

#endif
