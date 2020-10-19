#include "pch.h"
#include "types.h"
#include "dllmain.h"
#include "input_hook.h"
#include "keyboard.h"

#define GXLPARAM(lp) ((short)LOWORD(lp))
#define GYLPARAM(lp) ((short)HIWORD(lp))


HWND target_window = nullptr;
WNDPROC original_window_process = nullptr;
csnow_array_bit<8> key_states_menu[MAX_KEYS];

static std::set<InputHook::t_keyboard_fn> g_keyboard_functions;

void InputHook::keyboard_handler_register(const t_keyboard_fn function)
{
	g_keyboard_functions.insert(function);
}

void InputHook::keyboard_handler_unregister(const t_keyboard_fn function)
{
	g_keyboard_functions.erase(function);
}

InitlisationErrors InputHook::initialize(const HWND h_window)
{
	original_window_process = reinterpret_cast<WNDPROC>(SetWindowLongPtr(h_window, GWLP_WNDPROC, static_cast<__int3264>(reinterpret_cast<LONG_PTR>(window_process))));
	if (original_window_process == nullptr)
		return KEYBOARD_ERROR;
	keyboard_handler_register(on_keyboard_message);
	return SUCCESS;
}

void InputHook::remove()
{
	SetWindowLongPtr(initialisation::windowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(original_window_process));
}


LRESULT APIENTRY window_process(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	if (umsg == WM_KEYDOWN)
		key_states_menu[wparam].set_bit(KEY_STATE_PRESSED);
	else if (umsg == WM_KEYUP)
		key_states_menu[wparam] = false;
	return CallWindowProcA(original_window_process, hwnd, umsg, wparam, lparam);
}
