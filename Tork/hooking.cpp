#include "pch.h"
#include "types.h"
#include "hooking.h"
#include "minhook/include/MinHook.h"
#include "signatures.h"
#include "dllmain.h"
#include "input.h"
#include "user_interface.h"

bool(*original_is_dlc_present)(DWORD dlc) = nullptr;
bool __cdecl hooked_is_dlc_present(const DWORD dlc)
{
	if (uninjecting)
		return original_is_dlc_present(dlc);

	static uint64_t last_frame = 0;
	if (*m_frame_count > last_frame)
	{
		try
		{
			//drawControls();
			drawMenu();
			feature::addFooter();
		}
		catch (const std::runtime_error& re)
		{
			console::consoleLog("RUNTIME EXCEPTION", re.what());
		}
		catch (const std::exception& ex)
		{
			console::consoleLog("KNOWN EXCEPTION", ex.what());
		}
		catch (...)
		{
			console::consoleLog("UNKNOWN EXCEPTION", "Memory Exception!");
		}
		controls();
		last_frame = *m_frame_count;
	}

	return original_is_dlc_present(dlc);
}

bool initialiseHooking()
{
	MH_Initialize();
	const MH_STATUS status = MH_CreateHook(dlc::is_dlc_present, hooked_is_dlc_present, reinterpret_cast<void**>(&original_is_dlc_present));
	if (status != MH_OK && status != MH_ERROR_ALREADY_CREATED || MH_EnableHook(dlc::is_dlc_present) != MH_OK)
		return HOOK_ERROR;
	return SUCCESS;
}