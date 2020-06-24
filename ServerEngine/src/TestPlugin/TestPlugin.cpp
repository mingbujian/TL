#include "TestPlugin.h"

#ifdef NF_DYNAMIC_PLUGIN
NF_EXPORT void DllStartPlugin(IPluginManager* pm)
{
    CREATE_PLUGIN(pm, TestPlugin)

};

NF_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, TestPlugin)
};
#endif

const int TestPlugin::GetPluginVersion()
{
    return 0;
}

const std::string TestPlugin::GetPluginName()
{
    return "";
}

void TestPlugin::Install()
{
}

void TestPlugin::Uninstall()
{
}

bool TestPlugin::Execute()
{
    static int nCount = 0;
    std::cout << "frame times:" << ++nCount << endl;
    return true;
}