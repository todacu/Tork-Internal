#include "pch.h"
#include "dllmain.h"
#include "types.h"
#include "keyboard.h"
#include "user_interface.h"
#include "signatures.h"
#include "features.h"

bool uninjecting = false;
void shouldUninject()
{
	if (GetAsyncKeyState(VK_F11))
	{
		uninjecting = true;
		CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(uninject), nullptr, NULL, nullptr);
	}
}

ULONGLONG lastUsedController = GetTickCount64();
void controls()
{
	if (!Features::Controls::usingController)
	{
		if (get_key(MENU_OPEN, true, 5000, 50))
		{
			menuParams::menuOpen = !menuParams::menuOpen;
		}
		if (get_key(MENU_UP, true, 300, 50))
		{
			if (menuParams::selectedFeature > 1)
				menuParams::selectedFeature--;
			else
				menuParams::selectedFeature = menuParams::numberOfFeatures;
		}
		if (get_key(MENU_DOWN, true, 300, 50))
		{
			if (menuParams::selectedFeature < menuParams::numberOfFeatures)
				menuParams::selectedFeature++;
			else
				menuParams::selectedFeature = 1;
		}
		if (get_key(MENU_BACK, true, 5000, 50))
		{
			if (menuNavigation::subMenus.size() <= 1)
			{
				menuParams::menuOpen = false;
			}
			else
			{
				menuParams::selectedFeature = menuNavigation::lastSelectedFeature.back();
				menuNavigation::lastSelectedFeature.pop_back();
				menuNavigation::subMenus.pop_back();
			}
		}
	}
	if (get_key(MENU_SELECT, true, 300, 50))
	{
		menuNavigation::selected = true;
	}

	if (Features::Controls::usingController)
	{
		if (GetTickCount64() > lastUsedController + 150)
		{
			if ((game_controls::is_control_pressed(2, WEAPON_WHEEL) && (game_controls::is_control_pressed(2, TAKE_COVER) || game_controls::is_control_pressed(2, DIVE))))
			{

				menuParams::menuOpen = !menuParams::menuOpen;
			}
			lastUsedController = GetTickCount64();
		}
		if (game_controls::is_control_just_pressed(2, PHONE_UP))
		{
			if (menuParams::selectedFeature > 1)
				menuParams::selectedFeature--;
			else
				menuParams::selectedFeature = menuParams::numberOfFeatures;
		}
		if (game_controls::is_control_just_pressed(2, PHONE_DOWN))
		{
			if (menuParams::selectedFeature < menuParams::numberOfFeatures)
				menuParams::selectedFeature++;
			else
				menuParams::selectedFeature = 1;
		}
		if (game_controls::is_control_just_pressed(2, PHONE_CANCEL) || game_controls::is_control_just_pressed(2, ControlMeleeAttackLight))
		{
			if (menuNavigation::subMenus.size() <= 1)
			{
				menuParams::menuOpen = false;
			}
			else
			{
				menuParams::selectedFeature = menuNavigation::lastSelectedFeature.back();
				menuNavigation::lastSelectedFeature.pop_back();
				menuNavigation::subMenus.pop_back();
			}
		}
		if (game_controls::is_control_just_pressed(2, PHONE_SELECT))
		{
			menuNavigation::selected = true;
		}


		if (menuParams::menuOpen)
		{
			game_controls::disable_control_action(2, ControlPhone, true);
			game_controls::disable_control_action(2, ControlFrontendDown, true);
			game_controls::disable_control_action(2, ControlFrontendLeft, true);
			game_controls::disable_control_action(2, ControlFrontendUp, true);
			game_controls::disable_control_action(2, ControlFrontendRight, true);
			game_controls::disable_control_action(2, ControlScriptPadUp, true);
			game_controls::disable_control_action(2, ControlScriptPadDown, true);
			game_controls::disable_control_action(2, ControlScriptPadLeft, true);
			game_controls::disable_control_action(2, ControlScriptPadRight, true);
			game_controls::disable_control_action(2, ControlCharacterWheel, true);
			game_controls::disable_control_action(2, ControlVehicleHeadlight, true);
			game_controls::disable_control_action(2, ControlVehicleRadioWheel, true);
			game_controls::disable_control_action(2, ControlVehicleNextRadio, true);
			game_controls::disable_control_action(2, ControlVehiclePrevRadio, true);
			game_controls::disable_control_action(2, ControlVehicleNextRadioTrack, true);
			game_controls::disable_control_action(2, ControlVehiclePrevRadioTrack, true);
			game_controls::disable_control_action(2, ControlCinematicSlowMo, true);
			game_controls::disable_control_action(2, ControlVehicleFlyAttackCamera, true);
			game_controls::disable_control_action(2, ControlVehicleCinCam, true);
			game_controls::disable_control_action(2, ControlHUDSpecial, true);
		}
	}
	shouldUninject();
}