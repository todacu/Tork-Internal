#pragma once
#ifndef __FEATURES_H__
#define __FEATURES_H__

namespace Features
{
	namespace Player
	{
		extern bool godmode;
		extern bool neverWanted;
		extern bool alwaysWanted;
		extern bool selfRadio;
		extern bool noRagdoll;
		extern bool superJump;
		extern bool fastRun;
	    extern bool fastSwim;
	}
	namespace Spotify
	{
		extern bool spotifyRadioIntegration;
	}
	namespace Discord
	{
		extern bool discordIntegration;
	}
	namespace Vehicle
	{
		extern bool godmode;
		extern bool hornBoost;
		extern bool instantBrake;
	}
	namespace Controls
	{
		extern bool usingController;
	}
	namespace Weapon
	{
		extern bool explosiveAmmo;
		extern bool explosiveMelee;
		extern bool fireAmmo;
		extern bool aimbot;
	}
	namespace Interface
	{
		extern bool nearbyKillPeds;
	}
}

#endif