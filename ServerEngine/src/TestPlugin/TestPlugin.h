#pragma once
#include "dep/common/IPlugin.h"
#include "dep/common/IPluginManager.h"

//////////////////////////////////////////////////////////////////////////
class TestPlugin : public IPlugin
{
public:
    TestPlugin(IPluginManager* p) : IPlugin(p)
    {
    }

    ~TestPlugin(){}

    virtual const int GetPluginVersion() override;
    virtual const std::string GetPluginName() override;
    virtual void Install() override;
    virtual void Uninstall() override;

    virtual bool Execute() override;
};