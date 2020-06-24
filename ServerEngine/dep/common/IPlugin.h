#ifndef NFI_PLUGIN_H
#define NFI_PLUGIN_H

#include <iostream>
#include <assert.h>
#include "IPluginManager.h"

#define CREATE_PLUGIN(pManager, className)  IPlugin* pCreatePlugin##className = new className(pManager);\
        pManager->Registered( pCreatePlugin##className );

#define DESTROY_PLUGIN(pManager, className) pManager->UnRegistered( pManager->FindPlugin((#className)) );

/*
#define REGISTER_COMPONENT(pManager, className)  NFIComponent* pRegisterComponent##className= new className(pManager); \
    pRegisterComponent##className->strName = (#className); \
    pManager->AddComponent( (#className), pRegisterComponent##className );

#define UNREGISTER_COMPONENT(pManager, className) NFIComponent* pRegisterComponent##className =  \
        dynamic_cast<NFIComponent*>( pManager->FindComponent( (#className) ) ); pManager->RemoveComponent( (#className) ); delete pRegisterComponent##className;
*/

class IPluginManager;

class IPlugin
{

public:
	IPlugin(IPluginManager* p) : pPluginManager(p)
	{
	}
    virtual ~IPlugin()
	{
	}
    virtual const int GetPluginVersion() = 0;
    virtual const std::string GetPluginName() = 0;

    virtual void Install() = 0;
	virtual void Uninstall() = 0;

    virtual bool Awake() { return true; }
    virtual bool Init() { return true; }
    virtual bool AfterInit() { return true; }
    virtual bool CheckConfig() { return true; }
	virtual bool ReadyExecute() { return true; }
    virtual bool Execute() { return true; }
    virtual bool BeforeShut() { return true; }
    virtual bool Shut() { return true; }
    virtual bool Finalize() { return true; }
	virtual bool OnReloadPlugin() { return true; }
	virtual IPluginManager* GetPluginManager() const
	{
		return pPluginManager;
	}
protected:
	IPluginManager* pPluginManager = NULL;
};

#endif
