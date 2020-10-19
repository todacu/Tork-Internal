#include "pch.h"
#include "discord_int.h"
#include "features.h"
#include "Discord/include/discord_register.h"
#include "Discord/include/discord_rpc.h"
#pragma comment(lib,"Discord/lib/discord-rpc.lib")

void UpdatePresence()
{
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.startTimestamp = time(0);
	discordPresence.largeImageText = "DiscordInt";
	Discord_UpdatePresence(&discordPresence);
}

void setDiscordToggle(const bool toggle)
{
	if (!toggle) 
	{
		Discord_Shutdown();
		return;
	}
	else 
	{
		DiscordEventHandlers handlers;
		Discord_Initialize("554847971099934730", &handlers, 1, "");
		UpdatePresence();
	}
}