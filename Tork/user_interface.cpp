#include "pch.h"
#include "types.h"
#include "user_interface.h"
#include "signatures.h"
#include "vector.h"
#include "keyboard.h"
#include "reclass.h"
#include "functions.h"
#include "features.h"

namespace box {
	float x = .935f, y = .15f;
	float w = .1f, h = .235f;
	float offset = .011f;
}

namespace menuPosition {
	float x = .120f, y = .015f;
	float w = .215f, h = .085f;
}

namespace menuParams {
	int numberOfFeatures = 0;
	int selectedFeature = 1;
	int alignment = 1;
	int titleAlignment = 1;
	int font = 4;
	int titleFont = 2;
	bool center = false;
	float featureTextSize;
	ccolour selectedColour = { CWHITE };
	ccolour unselectedColour = { CWHITE };
	ccolour arrowColour = { 255,255,255,255 };
	float feautureFontSize = .45f;
	float titleFontSize = .6f;
	float feautureGap = .04f;
	float feautureHeight = .036f;
	float textOffset = .02f;
	float featureOffset = 0.046f; // 0.044f;
	bool menuOpen = true;
}

namespace menuNavigation
{
	bool selected = false;
	const char* mainMenuTitle = "~r~SYMMETRY ~s~GTA V MENU";
	std::vector<int> lastSelectedFeature;
	std::vector<const char*> subMenus = { mainMenuTitle };
	int selectedPlayer;
}

namespace game
{
	void drawText(const char* t_text, const p2 t_position, const int t_font, const float t_size, const int t_alignment, const ccolour t_colour)
	{
		m_text_info->i_font = t_font;
		m_text_info->set_scale(t_size);
		m_text_info->set_color(t_colour);
		m_text_info->f_text_wrap_start = 0.0f;
		m_text_info->f_text_wrap_end = 1.0f;
		m_text_info->unk3 = t_alignment;
		m_text_info->bt_drop_shadow = 1;
		m_text_info->bt_text_outline = 1;
		ui::set_text_entry("STRING");
		ui::add_text_component_substring_player_name(&t_text[0u]);
		ui::draw_text(t_position.x, t_position.y);
	}
}

void watermark()
{
	game::drawText("Symmetry Menu", { .0025f, .0025f }, 4, .25f, 1, { CWHITE });
}

namespace feature
{
	void clearMenu()
	{
		menuParams::numberOfFeatures = 0;
	}

	void addFooter()
	{
		if (!menuParams::menuOpen)
			return;
		char temp[0xA];
		sprintf_s(temp, "%i / %i", menuParams::selectedFeature, menuParams::numberOfFeatures);
		game::drawText(temp, { menuPosition::x - (!menuParams::titleAlignment ? 0.0f : 0.1f) - 0.0125f, (menuParams::numberOfFeatures + 1) * menuParams::feautureGap + (menuPosition::y + .06f) }, 4, menuParams::titleFontSize - .175f, menuParams::titleAlignment, menuParams::unselectedColour);
		ui::draw_rect(0, (menuParams::numberOfFeatures + 1) * menuParams::feautureGap + (menuPosition::y + .061f) + 0.015f, menuPosition::w - .125f, menuParams::feautureHeight + (menuParams::feautureHeight / 4), CBLACK);
	}

	void addTitle(const char* title)
	{
		game::drawText(title, { menuPosition::x - (!menuParams::titleAlignment ? 0.0f : 0.1f) - 0.0125f, menuPosition::y + 0.0275f }, menuParams::titleFont, menuParams::titleFontSize, menuParams::titleAlignment, menuParams::unselectedColour);
		ui::draw_rect(0, menuPosition::y + 0.048f, menuPosition::w + .2f, menuParams::feautureHeight + (menuParams::feautureHeight / 3), CBLACK);
	}

	bool addVehicle(const char* title, DWORD vehicle_hash, cped* ped, ccolour colour)
	{
		bool ret = addFeat(title, nullptr, colour);
		if (ret)
		{
			Functions::Player::spawnVehicle(vehicle_hash, ped);
		}
		return ret;
	}

	bool addFeat(const char* title, void(*t_callback)(), ccolour colour)
	{
		menuParams::numberOfFeatures++;

		ccolour backColour = { CGREY };
		if (menuParams::selectedFeature == menuParams::numberOfFeatures)
		{
			backColour = { CLIGHTGREY };
		}

		if (menuParams::numberOfFeatures <= 16 && menuParams::selectedFeature <= 16)
		{
			game::drawText(title, { menuPosition::x - (!menuParams::alignment ? 0.0f : 0.1f), menuParams::numberOfFeatures * menuParams::feautureGap + (menuPosition::y + menuParams::featureOffset) }, menuParams::font, menuParams::feautureFontSize, menuParams::alignment, menuParams::selectedFeature == menuParams::numberOfFeatures ? menuParams::selectedColour : menuParams::unselectedColour);
			ui::draw_rect(menuPosition::x - (!menuParams::center ? 0.0f : 0.1f), menuParams::numberOfFeatures * menuParams::feautureGap + (menuPosition::y + .061f), menuPosition::w, menuParams::feautureHeight, backColour.r, backColour.g, backColour.b, backColour.a);
		}
		else if (menuParams::numberOfFeatures > menuParams::selectedFeature - 16 && menuParams::numberOfFeatures <= menuParams::selectedFeature)
		{
			game::drawText(title, { menuPosition::x - (!menuParams::alignment ? 0.0f : 0.1f), (menuParams::numberOfFeatures - (menuParams::selectedFeature - 16)) * menuParams::feautureGap + (menuPosition::y + menuParams::featureOffset) }, menuParams::font, menuParams::feautureFontSize, menuParams::alignment, menuParams::selectedFeature == menuParams::numberOfFeatures ? menuParams::selectedColour : menuParams::unselectedColour);
			ui::draw_rect(menuPosition::x - (!menuParams::center ? 0.0f : 0.11f), (menuParams::numberOfFeatures - (menuParams::selectedFeature - 16)) * menuParams::feautureGap + (menuPosition::y + .061f), menuPosition::w, menuParams::feautureHeight, backColour.r, backColour.g, backColour.b, backColour.a);
		}

		if (menuNavigation::selected && menuParams::selectedFeature == menuParams::numberOfFeatures)
		{
			if (t_callback != nullptr)
				t_callback();
			menuNavigation::selected = false;
			return true;
		}
		return false;
	}

	bool addMenu(const char* title, const char* id, ccolour colour)
	{
		menuParams::numberOfFeatures++;

		ccolour backColour = { CGREY };
		if (menuParams::selectedFeature == menuParams::numberOfFeatures)
		{
			backColour = { CLIGHTGREY };
		}

		if (menuParams::numberOfFeatures <= 16 && menuParams::selectedFeature <= 16)
		{
			game::drawText(title, { menuPosition::x - (!menuParams::alignment ? 0.0f : 0.1f), menuParams::numberOfFeatures * menuParams::feautureGap + (menuPosition::y + menuParams::featureOffset) }, menuParams::font, menuParams::feautureFontSize, menuParams::alignment, menuParams::selectedFeature == menuParams::numberOfFeatures ? menuParams::selectedColour : menuParams::unselectedColour);
			game::drawText(">>", { menuPosition::x - (!menuParams::center ? 0.0f : 0.11f) + menuPosition::w / 2 - menuParams::textOffset, menuParams::numberOfFeatures * menuParams::feautureGap + (menuPosition::y + menuParams::featureOffset) }, menuParams::font, menuParams::feautureFontSize, menuParams::center, menuParams::arrowColour);
			ui::draw_rect(menuPosition::x - (!menuParams::center ? 0.0f : 0.1f), menuParams::numberOfFeatures * menuParams::feautureGap + (menuPosition::y + .061f), menuPosition::w, menuParams::feautureHeight, backColour.r, backColour.g, backColour.b, backColour.a);
		}
		else if (menuParams::numberOfFeatures > menuParams::selectedFeature - 16 && menuParams::numberOfFeatures <= menuParams::selectedFeature)
		{
			game::drawText(title, { menuPosition::x - (!menuParams::alignment ? 0.0f : 0.1f), (menuParams::numberOfFeatures - (menuParams::selectedFeature - 16)) * menuParams::feautureGap + (menuPosition::y + menuParams::featureOffset) }, menuParams::font, menuParams::feautureFontSize, menuParams::alignment, menuParams::selectedFeature == menuParams::numberOfFeatures ? menuParams::selectedColour : menuParams::unselectedColour);
			game::drawText(">>", { menuPosition::x - (!menuParams::center ? 0.0f : 0.11f) + menuPosition::w / 2 - menuParams::textOffset, (menuParams::numberOfFeatures - (menuParams::selectedFeature - 16)) * menuParams::feautureGap + (menuPosition::y + menuParams::featureOffset) }, menuParams::font, menuParams::feautureFontSize, menuParams::center, menuParams::arrowColour);
			ui::draw_rect(menuPosition::x - (!menuParams::center ? 0.0f : 0.11f), (menuParams::numberOfFeatures - (menuParams::selectedFeature - 16)) * menuParams::feautureGap + (menuPosition::y + .061f), menuPosition::w, menuParams::feautureHeight, backColour.r, backColour.g, backColour.b, backColour.a);
		}

		if (menuNavigation::selected && menuParams::selectedFeature == menuParams::numberOfFeatures)
		{
			menuNavigation::lastSelectedFeature.push_back(menuParams::selectedFeature);
			menuNavigation::subMenus.push_back(id);
			menuParams::selectedFeature = 1;
			menuParams::numberOfFeatures = 0;
			menuNavigation::selected = false;
			return true;
		}
		return false;
	}

	bool addPlayer(const char* title, int id, ccolour colour)
	{
		menuParams::numberOfFeatures++;

		ccolour backColour = { CGREY };
		if (menuParams::selectedFeature == menuParams::numberOfFeatures)
		{
			backColour = { CLIGHTGREY };
		}

		if (menuParams::numberOfFeatures <= 16 && menuParams::selectedFeature <= 16)
		{
			game::drawText(title, { menuPosition::x - (!menuParams::alignment ? 0.0f : 0.1f), menuParams::numberOfFeatures * menuParams::feautureGap + (menuPosition::y + menuParams::featureOffset) }, menuParams::font, menuParams::feautureFontSize, menuParams::alignment, menuParams::selectedFeature == menuParams::numberOfFeatures ? menuParams::selectedColour : menuParams::unselectedColour);
			game::drawText(">>", { menuPosition::x - (!menuParams::center ? 0.0f : 0.11f) + menuPosition::w / 2 - menuParams::textOffset, menuParams::numberOfFeatures * menuParams::feautureGap + (menuPosition::y + menuParams::featureOffset) }, menuParams::font, menuParams::feautureFontSize, menuParams::center, menuParams::arrowColour);
			ui::draw_rect(menuPosition::x - (!menuParams::center ? 0.0f : 0.1f), menuParams::numberOfFeatures * menuParams::feautureGap + (menuPosition::y + .061f), menuPosition::w, menuParams::feautureHeight, backColour.r, backColour.g, backColour.b, backColour.a);
		}
		else if (menuParams::numberOfFeatures > menuParams::selectedFeature - 16 && menuParams::numberOfFeatures <= menuParams::selectedFeature)
		{
			game::drawText(title, { menuPosition::x - (!menuParams::alignment ? 0.0f : 0.1f), (menuParams::numberOfFeatures - (menuParams::selectedFeature - 16)) * menuParams::feautureGap + (menuPosition::y + menuParams::featureOffset) }, menuParams::font, menuParams::feautureFontSize, menuParams::alignment, menuParams::selectedFeature == menuParams::numberOfFeatures ? menuParams::selectedColour : menuParams::unselectedColour);
			game::drawText(">>", { menuPosition::x - (!menuParams::center ? 0.0f : 0.11f) + menuPosition::w / 2 - menuParams::textOffset, (menuParams::numberOfFeatures - (menuParams::selectedFeature - 16)) * menuParams::feautureGap + (menuPosition::y + menuParams::featureOffset) }, menuParams::font, menuParams::feautureFontSize, menuParams::center, menuParams::arrowColour);
			ui::draw_rect(menuPosition::x - (!menuParams::center ? 0.0f : 0.11f), (menuParams::numberOfFeatures - (menuParams::selectedFeature - 16)) * menuParams::feautureGap + (menuPosition::y + .061f), menuPosition::w, menuParams::feautureHeight, backColour.r, backColour.g, backColour.b, backColour.a);
		}

		if (menuNavigation::selected && menuParams::selectedFeature == menuParams::numberOfFeatures)
		{
			menuNavigation::selectedPlayer = id;
			menuNavigation::lastSelectedFeature.push_back(menuParams::selectedFeature);
			menuNavigation::subMenus.push_back("Online Players");
			menuParams::selectedFeature = 1;
			menuParams::numberOfFeatures = 0;
			menuNavigation::selected = false;
			return true;
		}
		return false;
	}

	bool addBool(const char* title, bool& var, void(*t_callback)(const bool &val), bool tick, ccolour colour)
	{
		menuParams::numberOfFeatures++;

		ccolour backColour = { CGREY };
		if (menuParams::selectedFeature == menuParams::numberOfFeatures)
		{
			backColour = { CLIGHTGREY };
		}

		if (menuParams::numberOfFeatures <= 16 && menuParams::selectedFeature <= 16)
		{
			game::drawText(title, { menuPosition::x - (!menuParams::alignment ? 0.0f : 0.1f), menuParams::numberOfFeatures * menuParams::feautureGap + (menuPosition::y + menuParams::featureOffset) }, menuParams::font, menuParams::feautureFontSize, menuParams::alignment, menuParams::selectedFeature == menuParams::numberOfFeatures ? menuParams::selectedColour : menuParams::unselectedColour);
			game::drawText(var ? "ON" : "OFF", { menuPosition::x - (!menuParams::center ? 0.0f : 0.11f) + menuPosition::w / 2 - menuParams::textOffset, menuParams::numberOfFeatures * menuParams::feautureGap + (menuPosition::y + menuParams::featureOffset) }, menuParams::font, menuParams::feautureFontSize, menuParams::center, var ? ccolour{ CGREEN } : ccolour{ CRED1 });
			ui::draw_rect(menuPosition::x - (!menuParams::center ? 0.0f : 0.1f), menuParams::numberOfFeatures * menuParams::feautureGap + (menuPosition::y + .061f), menuPosition::w, menuParams::feautureHeight, backColour.r, backColour.g, backColour.b, backColour.a);
		}
		else if (menuParams::numberOfFeatures > menuParams::selectedFeature - 16 && menuParams::numberOfFeatures <= menuParams::selectedFeature)
		{
			game::drawText(title, { menuPosition::x - (!menuParams::alignment ? 0.0f : 0.1f), (menuParams::numberOfFeatures - (menuParams::selectedFeature - 16)) * menuParams::feautureGap + (menuPosition::y + menuParams::featureOffset) }, menuParams::font, menuParams::feautureFontSize, menuParams::alignment, menuParams::selectedFeature == menuParams::numberOfFeatures ? menuParams::selectedColour : menuParams::unselectedColour);
			game::drawText(var ? "ON" : "OFF", { menuPosition::x - (!menuParams::center ? 0.0f : 0.11f) + menuPosition::w / 2 - menuParams::textOffset, (menuParams::numberOfFeatures - (menuParams::selectedFeature - 16)) * menuParams::feautureGap + (menuPosition::y + menuParams::featureOffset) }, menuParams::font, menuParams::feautureFontSize, menuParams::center, var ? ccolour{ CGREEN } : ccolour{ CRED1 });
			ui::draw_rect(menuPosition::x - (!menuParams::center ? 0.0f : 0.11f), (menuParams::numberOfFeatures - (menuParams::selectedFeature - 16)) * menuParams::feautureGap + (menuPosition::y + 0.048f), menuPosition::w, menuParams::feautureHeight, backColour.r, backColour.g, backColour.b, backColour.a);
		}

		if (menuNavigation::selected && menuParams::selectedFeature == menuParams::numberOfFeatures)
		{
			var = !var;

			if (var && t_callback != nullptr)
			{
				if (!tick)
				{
					initialisation::enabledFeatures.push_back(var);
					initialisation::enabledFeaturesCallback.push_back(t_callback);
					initialisation::enabledFeaturesName.push_back(title);
				}
				else
				{
					initialisation::enabledFeaturesTick.push_back(var);
					initialisation::enabledFeaturesCallbackTick.push_back(t_callback);
					initialisation::enabledFeaturesNameTick.push_back(title);
				}
			}
			menuNavigation::selected = false;


			if (!var && t_callback != nullptr)
			{
				if (!tick)
				{
					for (int i = 0; i < initialisation::enabledFeaturesCallback.size(); ++i)
					{
						if (initialisation::enabledFeaturesCallback[i] == t_callback)
						{
							initialisation::enabledFeaturesCallback.erase(initialisation::enabledFeaturesCallback.begin() + i);
							initialisation::enabledFeatures.erase(initialisation::enabledFeatures.begin() + i);
							initialisation::enabledFeaturesName.erase(initialisation::enabledFeaturesName.begin() + i);
						}
					}
				}
				else
				{
					for (int i = 0; i < initialisation::enabledFeaturesCallbackTick.size(); ++i)
					{
						if (initialisation::enabledFeaturesCallbackTick[i] == t_callback)
						{
							initialisation::enabledFeaturesCallbackTick.erase(initialisation::enabledFeaturesCallbackTick.begin() + i);
							initialisation::enabledFeaturesTick.erase(initialisation::enabledFeaturesTick.begin() + i);
							initialisation::enabledFeaturesNameTick.erase(initialisation::enabledFeaturesNameTick.begin() + i);
						}
					}
				}
			}

			if (t_callback != nullptr)
				t_callback(var);

			return true;
		}

		return false;
	}
}


void drawControls()
{
	const char* information1 =
		"\n\n"
		"~g~Open:~s~ INSERT\n"
		"~g~BACK:~s~ NUMPAD 0\n"
		"~g~NAV UP:~s~ NUMPAD 8\n"
		"~g~NAV DOWN:~s~ NUMPAD 2\n";
	const char* information2 =
		"\n\n\n\n\n\n"
		"~g~NAV LEFT:~s~ NUMPAD 4\n"
		"~g~NAV RIGHT:~s~ NUMPAD 6\n"
		"~g~NAV SELECT:~s~ NUMPAD 5\n";
	game::drawText("Controls", { box::x, box::y - (box::h / 2) }, 4, .55f, 0, { CWHITE });
	game::drawText(information1, { box::x - (box::w / 2) + box::offset, box::y - (box::h / 2) }, 4, .4f, 1, { CWHITE });
	game::drawText(information2, { box::x - (box::w / 2) + box::offset, box::y - (box::h / 2) }, 4, .4f, 1, { CWHITE });
	ui::draw_rect(box::x, box::y, box::w, box::h, CBLACK);
}