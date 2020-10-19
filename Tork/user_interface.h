#pragma once
#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "reclass.h"

void drawMenu();
void drawControls();
void watermark();


namespace menuParams {
	extern int numberOfFeatures;
	extern int selectedFeature;
	extern bool menuOpen;
}

namespace menuNavigation
{
	extern bool selected;
	extern const char* mainMenuTitle;
	extern std::vector<int> lastSelectedFeature;
	extern std::vector<const char*> subMenus;
	extern int selectedPlayer;
}

namespace feature
{
	void clearMenu();
	void addTitle(const char* title);
	bool addMenu(const char* title, const char* id, ccolour colour = { CWHITE });
	bool addPlayer(const char* title, int id, ccolour colour = { CWHITE });
	bool addBool(const char* title, bool& var, void(*t_callback)(const bool& val) = nullptr, bool tick = false, ccolour colour = { CWHITE });
	bool addFeat(const char* title, void(*t_callback)() = nullptr, ccolour colour = { CWHITE });
	bool addVehicle(const char* title, DWORD vehicle_hash, cped* ped, ccolour colour = { CWHITE });
	void addFooter();
}

#endif