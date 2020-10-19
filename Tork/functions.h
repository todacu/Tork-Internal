#pragma once
#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

namespace Functions
{
	uint8_t getPlayerId();
	bool isPlayerConnected(const uint8_t playerId);
	float deg_to_rad(const float degs);
	float rad_to_deg(const float rads);
	float getDist(const v3 from, const v3 to);
	bool worldToScreen(const vector3 pos, v2& out);
	float angleDifference(const v3 viewAngle, const v3 dst);

	namespace Interface
	{
		void pedInterface(const char* type);
		void nearbyKillPeds(const bool& val);
	}
	namespace Player
	{
		void godmode(const bool &val);
		void suicide();
		void neverWanted(const bool& val);
		void alwaysWanted(const bool& val);
		void noRagdoll(const bool& val);
		uint32_t spawnVehicle(const DWORD model, cped* ped);
		void selfRadio(const bool& val);
		void superJump(const bool& val);
		void frameFlags();
		void refillHealthArmour();
		void fastRun(const bool& val);
		void fastSwim(const bool& val);
		void aimbot(const bool& val);
	}
	namespace Spotify
	{
		void spotifyRadioIntegration(const bool& val);
	}
	namespace Discord
	{
		void discordIntegration(const bool& val);
	}
	namespace Vehicle
	{
		void godmode(const bool& val);
		void hornBoost(const bool& val);
		void repair();
		void instantBrake(const bool& val);
	}
	namespace Weapon
	{
		void explosiveMelee(const bool& val);
		void explosiveAmmo(const bool& val);
		void fireAmmo(const bool& val);
	}
	namespace FunctionRepeater
	{
		DWORD WINAPI featureRepeaterThread();
	}
}

#endif