#include "pch.h"
#include "types.h"
#include "user_interface.h"
#include "menu.h"
#include "signatures.h"
#include "functions.h"
#include "features.h"

cped* myPed;
cped* selectedPed;
uint8_t myId;
void drawMenu()
{
	myPed = m_pworld->m_local_ped;
	if (myPed == nullptr)
		return;
	if (m_network_manager == nullptr)
		return;
	myId = Functions::getPlayerId();
	if (Functions::isPlayerConnected(menuNavigation::selectedPlayer) && menuNavigation::selectedPlayer != myId)
		selectedPed = m_network_manager->m_players[menuNavigation::selectedPlayer]->m_player_info->m_player_ped;
	else
		selectedPed = myPed;

	watermark();
	if (!menuParams::menuOpen)
		return;

	feature::clearMenu();
	if (strcmp(menuNavigation::subMenus.back(), "Online Players") == 0)
		feature::addTitle(selectedPed->m_player_info->m_name);
	else
		feature::addTitle(menuNavigation::subMenus.back());


	if (strcmp(menuNavigation::subMenus.back(), menuNavigation::mainMenuTitle) == 0)
	{
		feature::addMenu("Client", "Client");
		feature::addMenu("Network", "Network");
		feature::addMenu("Settings", "Settings");

		if (feature::addFeat("Debug Info"))
		{
			console::consoleLog("", "");
			console::consoleLog("", "-------------------------");

			console::consoleLog("\tHealth: ", "%f", myPed->m_health);
			console::consoleLog("\tArmour: ", "%f", myPed->m_armour);
			if (myPed->inVehicle()) {
				console::consoleLog("\tHealth: ", "%f", myPed->m_latest_vehicle->m_health);
				console::consoleLog("\tSpeed: ", "%f", vehicle::get_vehicle_forward_speed(myPed->m_latest_vehicle));
			}

			console::consoleLog("", "-------------------------");
			console::consoleLog("", "");
		}
	}
	else if (strcmp(menuNavigation::subMenus.back(), "Client") == 0)
	{
		feature::addMenu("Player", "Player");
		feature::addMenu("Cash", "Cash");
		feature::addMenu("Teleport", "Teleport");
		feature::addMenu("Vehicle", "Vehicle");
		feature::addMenu("Weapon", "Weapon");
		feature::addMenu("Recovery", "Recovery");
		feature::addMenu("World", "World");
	}
	else if (strcmp(menuNavigation::subMenus.back(), "Player") == 0)
	{
		feature::addBool("Godmode", Features::Player::godmode, Functions::Player::godmode);
		feature::addFeat("Refill Health & Armour", Functions::Player::refillHealthArmour);
		feature::addFeat("Suicide", Functions::Player::suicide);
		feature::addBool("Never Wanted", Features::Player::neverWanted, Functions::Player::neverWanted);
		feature::addBool("Always Wanted", Features::Player::alwaysWanted, Functions::Player::alwaysWanted);
		feature::addBool("Fast Run", Features::Player::fastRun, Functions::Player::fastRun);
		feature::addBool("Fast Swim", Features::Player::fastSwim, Functions::Player::fastSwim);
		feature::addBool("Self Radio", Features::Player::selfRadio, Functions::Player::selfRadio);
		feature::addBool("No Ragdoll", Features::Player::noRagdoll, Functions::Player::noRagdoll);
		feature::addBool("Super Jump", Features::Player::superJump, Functions::Player::superJump, ON_TICK);
	}
	else if (strcmp(menuNavigation::subMenus.back(), "Vehicle") == 0)
	{
		feature::addVehicle("Spawn Adder", 0xb779a091, myPed);
		feature::addBool("Godmode", Features::Vehicle::godmode, Functions::Vehicle::godmode);
		feature::addBool("Horn Boost", Features::Vehicle::hornBoost, Functions::Vehicle::hornBoost);
		feature::addFeat("Repair", Functions::Vehicle::repair);
		feature::addBool("Instant Brake", Features::Vehicle::instantBrake, Functions::Vehicle::instantBrake);
	}
	else if (strcmp(menuNavigation::subMenus.back(), "Weapon") == 0)
	{
		feature::addBool("Explosive Ammo", Features::Weapon::explosiveAmmo, Functions::Weapon::explosiveAmmo, ON_TICK);
		feature::addBool("Explosive Melee", Features::Weapon::explosiveMelee, Functions::Weapon::explosiveMelee, ON_TICK);
		feature::addBool("Fire Ammo", Features::Weapon::fireAmmo, Functions::Weapon::fireAmmo, ON_TICK);
		feature::addBool("Aimbot", Features::Weapon::aimbot, Functions::Player::aimbot);

	}
	else if (strcmp(menuNavigation::subMenus.back(), "World") == 0)
	{
		feature::addBool("Kill Nearby Peds", Features::Interface::nearbyKillPeds, Functions::Interface::nearbyKillPeds);
	}
	else if (strcmp(menuNavigation::subMenus.back(), "Network") == 0)
	{
		feature::addPlayer(myPed->m_player_info->m_name, Functions::getPlayerId());
		for (uint8_t playerId = 0; playerId < 32; ++playerId)
		{
			if (!Functions::isPlayerConnected(playerId) || playerId == myId)
				continue;
			feature::addPlayer(m_network_manager->m_players[playerId]->m_player_info->m_name, playerId);
		}
	}
	else if (strcmp(menuNavigation::subMenus.back(), "Online Players") == 0)
	{
		feature::addMenu("Player", "Net Player");
		feature::addMenu("Cash", "Net Cash");
		feature::addMenu("Teleport", "Net Teleport");
		feature::addMenu("Vehicle", "Net Vehicle");
		feature::addMenu("Weapon", "Net Weapon");
		feature::addMenu("World", "Net World");
	}
	else if (strcmp(menuNavigation::subMenus.back(), "Settings") == 0)
	{
		feature::addBool("Spotify Radio Integration", Features::Spotify::spotifyRadioIntegration, Functions::Spotify::spotifyRadioIntegration);
		feature::addBool("Discord Presence Integration", Features::Discord::discordIntegration, Functions::Discord::discordIntegration);
		feature::addBool("Using Controller?", Features::Controls::usingController);
	}
}
