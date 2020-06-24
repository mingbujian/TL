#ifndef NFI_PLUGIN_MANAGER_H
#define NFI_PLUGIN_MANAGER_H

#include <functional>
#include <list>
#include "Platform.h"

class IPlugin;
typedef std::function<bool (const std::string& strFileName, std::string& strContent)> GET_FILECONTENT_FUNCTOR;

class IPluginManager
{
public:
    IPluginManager()
    {
    }

	/////////////////////
	virtual bool LoadPlugin() { return true; }
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

	/////////////////////
	virtual bool ReLoadPlugin(const std::string& strPluginDLLName) = 0;
    virtual void Registered(IPlugin* plugin) = 0;
    virtual void UnRegistered(IPlugin* plugin) = 0;
    virtual IPlugin* FindPlugin(const std::string& strPluginName) = 0;
    virtual int GetAppID() const = 0;
    virtual void SetAppID(const int nAppID) = 0;
    virtual bool IsRunningDocker() const = 0;
    virtual void SetRunningDocker(bool bDocker) = 0;
    virtual bool IsStaticPlugin() const = 0;
    virtual NFINT64 GetInitTime() const = 0;
    virtual NFINT64 GetNowTime() const = 0;
	virtual const std::string& GetConfigPath() const = 0;
	virtual void SetConfigPath(const std::string & strPath) = 0;
	virtual void SetConfigName(const std::string& strFileName) = 0;	
	virtual const std::string& GetConfigName() const = 0;
	virtual const std::string& GetAppName() const = 0;
	virtual void SetAppName(const std::string& strAppName) = 0;
	virtual const std::string& GetLogConfigName() const = 0;
	virtual void SetLogConfigName(const std::string& strName) = 0;
	virtual IPlugin* GetCurrentPlugin() = 0;
	virtual void SetCurrentPlugin(IPlugin* pPlugin) = 0;
	virtual void SetGetFileContentFunctor(GET_FILECONTENT_FUNCTOR fun) = 0;
	virtual bool GetFileContent(const std::string &strFileName, std::string &strContent) = 0;
};

#endif
