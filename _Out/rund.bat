cd /d %~dp0
cd Debug

echo Starting NFGameServer...
start "NFGameServer" "PluginLoader.exe" "Server=GameServer" "ID=6" "Plugin=Plugin.xml"

rem choice /t 2 /d y /n >nul
rem echo Starting NFProxyServer...
rem start "NFProxyServer" "PluginLoader.exe" "Server=ProxyServer" "ID=5" "Plugin=Plugin.xml"






