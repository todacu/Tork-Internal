#pragma once
#ifndef DLLMAIN_H
#define DLLMAIN_H

namespace console
{
	void consoleLog(const char* prefix, const char* message, ...);
}

namespace initialisation
{
	extern HMODULE dllBaseAddress;
	extern HWND windowHandle;
	extern bool injected;
	extern std::vector<bool>enabledFeatures;
	extern std::vector<void(*)(const bool& val)>enabledFeaturesCallback;
	extern std::vector<const char*>enabledFeaturesName;

	extern std::vector<bool>enabledFeaturesTick;
	extern std::vector<void(*)(const bool& val)>enabledFeaturesCallbackTick;
	extern std::vector<const char*>enabledFeaturesNameTick;
}

DWORD WINAPI uninject();

#endif