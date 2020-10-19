// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "types.h"
#include "hooking.h"
#include "signatures.h"
#include "minhook/include/MinHook.h"
#include "input_hook.h"
#include "keyboard.h"
#include "spotify_int.h"
#include "discord_int.h"
#include "features.h"
#include "functions.h"

namespace initialisation
{
	HMODULE dllBaseAddress;
	HWND windowHandle;
	bool injected;
	std::vector<bool>enabledFeatures;
	std::vector<void(*)(const bool& val)>enabledFeaturesCallback;
	std::vector<const char*>enabledFeaturesName;

	std::vector<bool>enabledFeaturesTick;
	std::vector<void(*)(const bool& val)>enabledFeaturesCallbackTick;
	std::vector<const char*>enabledFeaturesNameTick;
}

namespace console
{
	void initialiseConsole(const LPCWSTR title, const ClearConsole clear, ClosableConsole closable)
	{
		AllocConsole();
		FILE* stream;
		freopen_s(&stream, "CONOUT$", "w", stdout);
		SetConsoleTitle(title);

		if (!closable)
			EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_GRAYED);
		if (clear)
			system("cls");
	}

	void setConsoleColour(const ConsoleColours colour)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
	}

	void consoleLog(const char* prefix, const char* message, ...)
	{
		static char buffer[0xFF];
		va_list arguments;
		va_start(arguments, message);
		vsprintf_s(buffer, message, arguments);
		va_end(arguments);
		static char final[0xFF];
		sprintf_s(final, "%s", buffer);

		console::setConsoleColour(GREEN);
		std::cout << prefix;
		console::setConsoleColour(WHITE);
		std::cout << ": ";
		std::cout << final << "\n";
	}
}

void getWindow(const LPCWSTR windowClass)
{
	while (!initialisation::windowHandle)
		initialisation::windowHandle = FindWindow(windowClass, nullptr);
}

InitlisationErrors WINAPI initialiseMenu()
{
	console::initialiseConsole(L"Debug Log", CLEAR, UNCLOSABLE);
	console::consoleLog("HOOKING", "Console Initialised");

	getWindow(L"grcWindow");
	console::consoleLog("HOOKING", "Window Found");

	if (initialiseSignatures() != SUCCESS)
		return PATTERN_ERROR;
	console::consoleLog("HOOKING", "Signatures Initialised");

	if (InputHook::initialize(initialisation::windowHandle) == KEYBOARD_ERROR)
		return KEYBOARD_ERROR;
	console::consoleLog("HOOKING", "Keyboard Initialised");

	if (initialiseHooking() != SUCCESS)
		return HOOK_ERROR;
	console::consoleLog("HOOKING", "Hooking Initialised");

	console::consoleLog("STATE", "Ready");

	console::consoleLog("\nMOD VERSION", "%s", "1.0");
	console::consoleLog("GAME VERSION", "%s\n\n", m_game_version->m_version);
	

	initialisation::injected = true;
	return SUCCESS;
}

DWORD WINAPI uninject()
{ 
	for (int i = 0; i < initialisation::enabledFeatures.size(); ++i)
	{
		if (initialisation::enabledFeatures[i])
			initialisation::enabledFeaturesCallback[i](false);
	}

	for (int i = 0; i < initialisation::enabledFeaturesTick.size(); ++i)
	{
		if (initialisation::enabledFeaturesTick[i])
			initialisation::enabledFeaturesCallbackTick[i](false);
	}

	console::consoleLog("\nSTATE", "Deactivated Features");
	Sleep(500);
	console::consoleLog("STATE", "Uninjected");
	if (Features::Discord::discordIntegration)
		setDiscordToggle(false);

	InputHook::keyboard_handler_unregister(on_keyboard_message);
	InputHook::remove();

	MH_DisableHook(&ResetWriteWatch);
	MH_RemoveHook(&ResetWriteWatch);

	MH_DisableHook(dlc::is_dlc_present);
	MH_RemoveHook(dlc::is_dlc_present);

	MH_Uninitialize();

	FreeLibraryAndExitThread(initialisation::dllBaseAddress, 0);
}

DWORD WINAPI timeout()
{
	Sleep(5000);
	if (!initialisation::injected)
		FreeLibraryAndExitThread(initialisation::dllBaseAddress, 0);
	return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		initialisation::dllBaseAddress = hModule;
		CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(initialiseMenu), nullptr, NULL, nullptr);
		CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(checkSpotifySong), nullptr, NULL, nullptr);
		CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(Functions::FunctionRepeater::featureRepeaterThread), nullptr, NULL, nullptr);
		CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(timeout), nullptr, NULL, nullptr);
	}
	return true;
}