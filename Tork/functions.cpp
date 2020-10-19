#include "pch.h"
#include "types.h"
#include "signatures.h"
#include "menu.h"
#include "spotify_int.h"
#include "discord_int.h"
#include "features.h"
#include "input.h"
#include "functions.h"


namespace Functions
{
	uint8_t getPlayerId()
	{
		if (*static_cast<uint8_t*>(m_player_online) != 0u)
			return m_network_manager->m_local_player->m_player_id;
		return 0;
	}

	float angleDifference(const v3 viewAngle, const v3 dst)
	{
		float num1 = viewAngle.x - dst.x;
		float num2 = viewAngle.y - dst.y;
		const bool  flag = 180.0 > num1;
		const int   num3 = 180.0 > num2 ? 1 : 0;
		if (!flag)
			num1 -= 360;
		if (num3 == 0)
			num2 -= 360;
		if (0.0 > num1)
			num1 = num1 - num1 - num1;
		if (0.0 > num2)
			num2 = num2 - num2 - num2;
		return (float)(num1 + (double)num2);
	}

	bool worldToScreen(const vector3 pos, v2& out)
	{
		vector3 tmp;

		float* view_matrix = m_view_port->fViewMatrix;

		tmp.x = view_matrix[1] * pos.x + view_matrix[5] * pos.y + view_matrix[9] * pos.z + view_matrix[13];
		tmp.y = view_matrix[2] * pos.x + view_matrix[6] * pos.y + view_matrix[10] * pos.z + view_matrix[14];
		tmp.z = view_matrix[3] * pos.x + view_matrix[7] * pos.y + view_matrix[11] * pos.z + view_matrix[15];

		if (tmp.z < 0.001f)
			return false;

		tmp.z = 1.0f / tmp.z;

		tmp.x *= tmp.z;
		tmp.y *= tmp.z;

		const uint32_t w = m_resolution->w;
		const uint32_t h = m_resolution->h;

		out.x = (w / 2.f + (.5f * tmp.x * w + 1.f)) / w;
		out.y = (h / 2.f - (.5f * tmp.y * h + 1.f)) / h;

		return !(out.x > 1.f || out.x < 0.f || out.y > 1.f || out.y < 0.f);
	}

	float deg_to_rad(const float degs)
	{
		return degs * 3.141592653589793f / 180.f;
	}

	float getDist(const v3 from, const v3 to)
	{
		return (float)sqrt(pow(double(from.x - to.x), 2.0) + pow(double(from.y - to.y), 2.0) + pow(double(from.z - to.z), 2.0));
	}

	float rad_to_deg(const float rads)
	{
		return rads * 57.295f;
	}

	bool isPlayerConnected(const uint8_t playerId)
	{
		return !!m_network_manager->m_players[playerId];
	}

	namespace Player
	{
		void godmode(const bool& val)
		{
			myPed->m_entity_proofs.m_split.m_invincible = val;
		}

		void suicide()
		{
			myPed->m_health = 0.f;
		}

		void noRagdoll(const bool& val)
		{
			myPed->m_no_ragdoll = val ? 1 : 32;
		}

		void refillHealthArmour()
		{
			myPed->m_health = myPed->m_max_health;
			myPed->m_armour = 100.f;
		}

		void fastRun(const bool& val)
		{
			myPed->m_player_info->m_run_speed_multiplier = val ? 2.f : 1.f;
		}

		void fastSwim(const bool& val)
		{
			myPed->m_player_info->m_swim_speed_multiplier = val ? 2.f : 1.f;
		}

		void frameFlags()
		{
			if (myPed->m_player_info == nullptr)
				return;

			const int super_jump = 64;
			const int explosive_melee = 32;
			const int fire_ammo = 16;
			const int explosive_ammo = 8;

			int flag = 0;

			if (Features::Player::superJump)
				flag += super_jump;
			if (Features::Weapon::explosiveMelee)
				flag += explosive_melee;
			if (Features::Weapon::fireAmmo)
				flag += fire_ammo;
			if (Features::Weapon::explosiveAmmo)
				flag += explosive_ammo;

			if (flag != 0)
				myPed->m_player_info->m_frame_flags = flag;
		}

		void superJump(const bool& val)
		{
			frameFlags();
		}

		void no_police_bypass(const bool toggle)
		{
			constexpr fiveBytes patched = { 0xB0, 0x00, 0xC3, 0x90, 0x90 };
			constexpr fiveBytes restore = { 0x48, 0x89, 0x5C, 0x24, 0x08 };
			if (m_no_police == nullptr)
				return;
			*m_no_police = toggle ? patched : restore;
		}

		void neverWanted(const bool& val)
		{
			myPed->m_player_info->m_wanted_level = 0;
			no_police_bypass(val);
		}

		void alwaysWanted(const bool& val)
		{
			myPed->m_player_info->m_wanted_level = 5;
			no_police_bypass(val);
			if (!val)
				myPed->m_player_info->m_wanted_level = 0;
		}

		void selfRadio(const bool& val)
		{
			audio::set_mobile_radio_enabled_during_gameplay(val);
			if (!val && isSongPlaying && Features::Spotify::spotifyRadioIntegration)
			{
				sendPlayKey();
				nowPlaying = "";
				lastNowPlaying = "";
				isSongPlaying = false;
			}
		}

		void aimbot(const bool& val)
		{
			if (!game_controls::is_control_pressed(2, ControlAim))
				return;
			if (myPed->inVehicle())
				return;

			Functions::Interface::pedInterface("AIMBOT");
		}

		uint32_t spawnVehicle(const DWORD model, cped* ped)
		{
			if (ped == nullptr)
				return 0;
			if (!streaming::is_model_in_cdimage(model))
				return 0;
			int modelTick = 0;
			while (modelTick < 10)
			{
				streaming::request_model(model);
				modelTick++;
				Sleep(5);
			}

			cmodel_info* newVehData = streaming::get_model_data(model, 0);
			float distance = newVehData->m_max_dimension_y;
			float heading = heading::get_entity_heading(utility::address_to_handle(ped));
			if (ped->inVehicle())
			{
				distance = distance + (ped->m_latest_vehicle->m_model_info->m_max_dimension_y / 2) + .75f;
				heading = heading::get_entity_heading(utility::address_to_handle(ped->m_latest_vehicle));
			}

			vector3 pos = { ped->m_navigation->m_position.x,0, ped->m_navigation->m_position.y,0, ped->m_navigation->m_position.z,0 };
			pos.x += distance * sin(deg_to_rad(heading) * -1);
			pos.y += distance * cos(deg_to_rad(heading));

			uint32_t spawnedVehicle = vehicle::create_vehicle(model, &pos, heading, true, false);
			if (spawnedVehicle)
			{
				const float speed = vehicle::get_vehicle_forward_speed(ped->m_latest_vehicle);
				vehicle::set_vehicle_forward_speed(spawnedVehicle, speed);
				ped::task_warp_ped_into_vehicle(utility::address_to_handle(myPed), spawnedVehicle, -1);
				vehicle::set_vehicle_engine_on(spawnedVehicle, true, true, 0);
				vehicle::set_vehicle_number_plate_text(spawnedVehicle, "TOM");
			}

			return spawnedVehicle;
		}
	}
	namespace Spotify
	{
		void spotifyRadioIntegration(const bool& val)
		{
			grabHwnd();
			if (val && !isSongPlaying)
			{
				sendPlayKey();
				isSongPlaying = true;
			}
			if (!val && isSongPlaying)
			{
				sendPlayKey();
				nowPlaying = "";
				lastNowPlaying = "";
				isSongPlaying = false;
			}
		}
	}
	namespace FunctionRepeater
	{
		ULONGLONG lastFunctionRepeat = GetTickCount64();
		ULONGLONG lastFunctionRepeatTick = GetTickCount64();
		DWORD WINAPI featureRepeaterThread()
		{
			while (!initialisation::injected)
				Sleep(25);

			while (!uninjecting)
			{
				if (GetTickCount64() > lastFunctionRepeat + 5) // Delayed Functions
				{
					for (int i = 0; i < initialisation::enabledFeaturesName.size(); ++i)
					{
						try
						{
							if (initialisation::enabledFeatures[i])
								initialisation::enabledFeaturesCallback[i](true);

						}
						catch (...)
						{
							console::consoleLog("REPEATER UNKNOWN EXCEPTION", "Memory Exception in %s!", initialisation::enabledFeaturesName[i]);
							for (int j = 0; j < initialisation::enabledFeaturesCallback.size(); ++j)
							{
								if (initialisation::enabledFeaturesCallback[j] == initialisation::enabledFeaturesCallback[i])
								{
									initialisation::enabledFeaturesCallback.erase(initialisation::enabledFeaturesCallback.begin() + j);
									initialisation::enabledFeatures.erase(initialisation::enabledFeatures.begin() + j);
									initialisation::enabledFeaturesName.erase(initialisation::enabledFeaturesName.begin() + j);
									console::consoleLog("ANTI CRASH", "%s has been removed from the repeater to prevent memory exceptions!", initialisation::enabledFeaturesName[i]);
								}
							}
						}
					}
					lastFunctionRepeat = GetTickCount64();
				}
				for (int i = 0; i < initialisation::enabledFeaturesNameTick.size(); ++i) // Tick Functions
				{
					try
					{
						if (initialisation::enabledFeaturesTick[i])
							initialisation::enabledFeaturesCallbackTick[i](true);

					}
					catch (...)
					{
						console::consoleLog("REPEATER UNKNOWN EXCEPTION", "Memory Exception in %s!", initialisation::enabledFeaturesNameTick[i]);
						for (int j = 0; j < initialisation::enabledFeaturesCallbackTick.size(); ++j)
						{
							if (initialisation::enabledFeaturesCallbackTick[j] == initialisation::enabledFeaturesCallbackTick[i])
							{
								initialisation::enabledFeaturesCallbackTick.erase(initialisation::enabledFeaturesCallbackTick.begin() + j);
								initialisation::enabledFeaturesTick.erase(initialisation::enabledFeaturesTick.begin() + j);
								initialisation::enabledFeaturesNameTick.erase(initialisation::enabledFeaturesNameTick.begin() + j);
								console::consoleLog("ANTI CRASH", "%s has been removed from the repeater to prevent memory exceptions!", initialisation::enabledFeaturesNameTick[i]);
							}
						}
					}
				}
			}
			return 0;
		}
	}
	namespace Discord
	{
		void discordIntegration(const bool& val)
		{
			setDiscordToggle(val);
		}
	}
	namespace Vehicle
	{
		void repair()
		{
			if (myPed->inVehicle())
			{
				if (myPed->m_latest_vehicle != nullptr)
				{
					vehicle::set_vehicle_fixed(utility::address_to_handle(myPed->m_latest_vehicle));
					vehicle::set_vehicle_dirt_level(utility::address_to_handle(myPed->m_latest_vehicle), 0.f);
				}
			}
		}

		void godmode(const bool& val)
		{
			if (myPed->inVehicle())
			{
				myPed->m_latest_vehicle->m_entity_proofs.m_split.m_invincible = val;
			}
		}


		void hornBoost(const bool& val)
		{
			if (!val)
				return;
			if (myPed->inVehicle() && game_controls::is_control_pressed(2, VEHICLE_HORN))
			{
				vehicle::set_vehicle_forward_speed(utility::address_to_handle(myPed->m_latest_vehicle), vehicle::get_vehicle_forward_speed(myPed->m_latest_vehicle) + .5f);
			}
		}

		void instantBrake(const bool& val)
		{
			if (!val)
				return;
			if (myPed->inVehicle() && game_controls::is_control_pressed(2, VEHICLE_HANDBRAKE))
			{
				vehicle::set_vehicle_forward_speed(utility::address_to_handle(myPed->m_latest_vehicle), 0.f);
			}
		}
	}
	namespace Weapon
	{
		void explosiveMelee(const bool& val)
		{
			Player::frameFlags();
		}

		void explosiveAmmo(const bool& val)
		{
			Player::frameFlags();
		}

		void fireAmmo(const bool& val)
		{
			Player::frameFlags();
		}
	}
	namespace Interface
	{
		bool isPed(cped* ped_ptr)
		{
			return ped_ptr->m_player_info == nullptr;
		}
		void pedInterface(const char* type)
		{
			creplay_interface_ped* list_of_peds = m_replay_interface->m_replay_interface_ped;
			for (uint32_t i = 0; i < list_of_peds->m_max_peds; ++i)
			{
				cped* ped_ptr = list_of_peds->get_ped(i);
				if (ped_ptr == nullptr)
					continue;
				if (ped_ptr == myPed)
					continue;

				if (type == "KILL")
				{
					if (!isPed(ped_ptr))
						continue;

					ped_ptr->m_health = 0.f;
				}
				if (type == "AIMBOT")
				{
					if (!isPed(ped_ptr))
						continue;
					if (ped_ptr->m_health == 0.f)
						continue;
					if (ped_ptr->m_type != 4 && ped_ptr->m_type != 5 && ped_ptr->m_type != 6)
						continue;

					v2   my_screen[2];
					bool on_screen = false;
					on_screen |= worldToScreen({ ped_ptr->m_visual_position.x, 0, ped_ptr->m_visual_position.y, 0, ped_ptr->m_visual_position.z + 1.0f, 0 }, my_screen[0]);
					on_screen |= worldToScreen({ ped_ptr->m_visual_position.x, 0, ped_ptr->m_visual_position.y, 0, ped_ptr->m_visual_position.z + 0.8f, 0 }, my_screen[1]);
					if (!on_screen)
						continue;

					ccurrent_ped_cam* camera = m_camera->m_gam_gameplay_director->m_current_ped_cam;
					if (camera != nullptr)
					{
						const v3 my_pos = camera->m_crosshair_location;
						const v3 target = ped_ptr->m_visual_position;
						const float distance = getDist(my_pos, target);

						v3 final_v3;
						final_v3.x = (target.x - my_pos.x) / distance;
						final_v3.y = (target.y - my_pos.y) / distance;
						final_v3.z = (target.z - my_pos.z) / distance;

						camera->m_viewing_angles = final_v3;
					}
				}
			}
		}
		void nearbyKillPeds(const bool& val)
		{
			pedInterface("KILL");
		}
	}
}
