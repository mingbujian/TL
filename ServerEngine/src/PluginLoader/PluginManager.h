#ifndef NF_PLUGIN_MANAGER_H
#define NF_PLUGIN_MANAGER_H

#include <map>
#include <string>
#include <time.h>
#include <thread>
#include "DynLib.h"
#include "Singleton.hpp"
#include "IPluginManager.h"
#include <vector>

class PluginManager;
extern PluginManager&  g_PluginManger;

class PluginManager : public IPluginManager
{
public:
    PluginManager();
    virtual ~PluginManager();

    virtual bool LoadPlugin() override;
    virtual bool Awake() override;
    virtual bool Init() override;
    virtual bool AfterInit() override;
    virtual bool CheckConfig() override;
    virtual bool ReadyExecute() override;
    virtual bool BeforeShut() override;
    virtual bool Shut() override;
    virtual bool Finalize() override;
    //////////////////////////////////////////////////////////////////////////

    virtual void Registered(IPlugin* pPlugin) override;
    virtual void UnRegistered(IPlugin* pPlugin) override;
    //////////////////////////////////////////////////////////////////////////

    virtual bool ReLoadPlugin(const std::string& strPluginDLLName) override;
    virtual IPlugin* FindPlugin(const std::string& strPluginName) override;
    virtual bool Execute() override;
    virtual int GetAppID() const override;
    virtual void SetAppID(const int nAppID) override;
    virtual bool IsRunningDocker() const override;
    virtual void SetRunningDocker(bool bDocker) override;
    virtual bool IsStaticPlugin() const override;
    virtual NFINT64 GetInitTime() const override;
    virtual NFINT64 GetNowTime() const override;
    virtual const std::string& GetConfigPath() const override;
    virtual void SetConfigPath(const std::string & strPath) override;
    virtual void SetConfigName(const std::string& strFileName) override;
    virtual const std::string& GetConfigName() const override;
    virtual const std::string& GetAppName() const override;
    virtual void SetAppName(const std::string& strAppName) override;
    virtual const std::string& GetLogConfigName() const override;
    virtual void SetLogConfigName(const std::string& strName) override;
    virtual IPlugin* GetCurrentPlugin() override;
    virtual void SetCurrentPlugin(IPlugin* pPlugin) override;
    virtual void SetGetFileContentFunctor(GET_FILECONTENT_FUNCTOR fun) override;
    virtual bool GetFileContent(const std::string &strFileName, std::string &strContent) override;

protected:
    bool LoadPluginConfig();

    bool LoadStaticPlugin();
    bool CheckStaticPlugin();

    bool LoadStaticPlugin(const std::string& strPluginDLLName);
    bool LoadPluginLibrary(const std::string& strPluginDLLName);
    bool UnLoadPluginLibrary(const std::string& strPluginDLLName);
    bool UnLoadStaticPlugin(const std::string& strPluginDLLName);

private:
    int mnAppID;
    bool mbIsDocker;
    bool mbStaticPlugin;
    NFINT64 mnInitTime;
    NFINT64 mnNowTime;
    std::string mstrConfigPath;
    std::string mstrConfigName;
    std::string mstrAppName;
    std::string mstrLogConfigName;

    IPlugin* mCurrentPlugin;

    typedef std::map<std::string, bool> PluginNameMap;
    typedef std::map<std::string, DynLib*> PluginLibMap;
    typedef std::map<std::string, IPlugin*> PluginInstanceMap;

    typedef void(* DLL_START_PLUGIN_FUNC)(IPluginManager* pm);
    typedef void(* DLL_STOP_PLUGIN_FUNC)(IPluginManager* pm);

    std::vector<std::string> mStaticPlugin;

    PluginNameMap mPluginNameMap;
    PluginLibMap mPluginLibMap;
    PluginInstanceMap mPluginInstanceMap;

    GET_FILECONTENT_FUNCTOR mGetFileContentFunctor;
};

#endif
