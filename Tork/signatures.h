#pragma once
#ifndef SIGNATURES_H
#define SIGNATURES_H

#include "memory.h"
#include "reclass.h"

extern TextInfo* m_text_info;
extern uint64_t* m_frame_count;
extern cnetwork_player_manager* m_network_manager;
extern cworld* m_pworld;
extern uint8_t* m_player_online;
extern fiveBytes* m_no_police;
extern MemoryPool** m_entity_pool;
extern cgta_time* m_time_struct;
extern cgame_version* m_game_version;
extern creplay_interface* m_replay_interface;
extern ccam_interface* m_camera;
extern Screen* m_resolution;
extern cviewport* m_view_port;

namespace ui
{
	typedef void(__cdecl* tdraw_rect)(float x, float y, float w, float h, int r, int g, int b, int a);
	extern tdraw_rect draw_rect;

	typedef bool(__cdecl* tset_text_entry)(const char* text);
	extern tset_text_entry set_text_entry;

	typedef bool(__cdecl* tadd_text_component_substring_player_name)(const char* text);
	extern tadd_text_component_substring_player_name add_text_component_substring_player_name;

	typedef bool(__cdecl* tdraw_text)(float x, float y);
	extern tdraw_text draw_text;
}


namespace dlc
{
	typedef bool(__cdecl* tis_dlc_present)(DWORD dlc);
	extern tis_dlc_present is_dlc_present;
}

namespace decorator
{
	typedef bool(*tdecor_set_int)(uint32_t entity, const char* name, int value);
	extern tdecor_set_int decor_set_int;
}

namespace streaming
{
	typedef void(__cdecl* trequest_model)(DWORD model_hash);
	extern trequest_model request_model;

	typedef bool(*thas_model_loaded)(DWORD model_hash);
	extern thas_model_loaded has_model_loaded;

	typedef bool(*tis_model_in_cdimage)(DWORD model_hash);
	extern tis_model_in_cdimage is_model_in_cdimage;

	typedef bool(*tset_model_as_no_longer_needed)(DWORD model_hash);
	extern tset_model_as_no_longer_needed set_model_as_no_longer_needed;

	typedef void(*trequest_anim_dict)(char* animation_dict);
	extern trequest_anim_dict request_anim_dict;

	typedef cmodel_info* (*tget_model_data)(uint32_t hash, __int64 data);
	extern tget_model_data get_model_data;
}

namespace audio
{
	typedef void(__cdecl* tset_mobile_radio_enabled_during_gameplay)(bool toggle);
	extern tset_mobile_radio_enabled_during_gameplay set_mobile_radio_enabled_during_gameplay;

	typedef int(__cdecl* tget_player_radio_station_index)();
	extern tget_player_radio_station_index get_player_radio_station_index;
}

namespace vehicle
{
	typedef int(*tcreate_vehicle)(DWORD model_hash, vector3* pos, float heading, bool networked, bool unk2);
	extern tcreate_vehicle create_vehicle;

	typedef void(*tset_vehicle_forward_speed)(uint32_t vehicle, float speed);
	extern tset_vehicle_forward_speed set_vehicle_forward_speed;

	typedef bool(*tis_player_pressing_horn)(uint8_t player_id);
	extern tis_player_pressing_horn is_player_pressing_horn;

	typedef bool(*tset_vehicle_engine_on)(uint32_t vehicle, bool val, bool instant, bool unk);
	extern tset_vehicle_engine_on set_vehicle_engine_on;

	typedef bool(*tset_vehicle_number_plate_text)(uint32_t vehicle, const char* text);
	extern tset_vehicle_number_plate_text set_vehicle_number_plate_text;

	typedef bool(*tset_vehicle_number_plate_index)(cvehicle* vehicle, int index);
	extern tset_vehicle_number_plate_index set_vehicle_number_plate_index;

	typedef bool(*tset_vehicle_mod_kit)(uint32_t vehicle, int modKit);
	extern tset_vehicle_mod_kit set_vehicle_mod_kit;

	typedef void(*tset_vehicle_fixed)(uint32_t vehicle);
	extern tset_vehicle_fixed set_vehicle_fixed;

	typedef void(*tset_vehicle_dirt_level)(uint32_t vehicle, float dirt_level);
	extern tset_vehicle_dirt_level set_vehicle_dirt_level;

	float get_vehicle_forward_speed(cvehicle* veh);
}

namespace heading
{
	typedef __int64(*tfunc1)(signed int a1);
	extern tfunc1 func1;
	typedef __int64(*tfunc2)(__int64 a1);
	extern tfunc2 func2;

	float get_entity_heading(int pedHandle);
}

namespace utility
{
	typedef uint32_t(*taddress_to_handle)(void* ent);
	extern taddress_to_handle address_to_handle;

	typedef void* (*thandle_to_address)(uint32_t handle);
	extern thandle_to_address handle_to_address;

	uintptr_t get_address_of_item_in_pool(MemoryPool* pool, const int handle);
	template <typename Rt> Rt* handle_to_ptr(const int handle)
	{
		const auto ptr = get_address_of_item_in_pool(*m_entity_pool, handle);
		if (ptr == 0)
			return nullptr;
		return *reinterpret_cast<Rt * *>(ptr + 8);
	}
}

namespace ped
{
	typedef bool(*ttask_warp_ped_into_vehicle)(int ped, int vehicle, int seat);
	extern ttask_warp_ped_into_vehicle task_warp_ped_into_vehicle;
}

namespace game_controls
{
	typedef bool(*tis_control_pressed)(int input_group, int control);
	extern tis_control_pressed is_control_pressed;

	typedef void(__cdecl* tdisable_control_action)(int input_group, int control, BOOL disable);
	extern tdisable_control_action disable_control_action;

	typedef bool(__cdecl* tis_control_just_pressed)(int input_group, int control);
	extern tis_control_just_pressed is_control_just_pressed;
}

bool initialiseSignatures();

template <typename T>
void set_pattern(const char* name, const char* pat, const char* mask, T** out, bool rel, int offset, int deref, int skip)
{
	T* ptr = nullptr;

	CPattern pattern(pat, mask);
	pattern.find(skip + 1);
	if (rel)
		ptr = pattern.get(skip).get_rel<T>(offset);
	else
		ptr = pattern.get(skip).get<T>(offset);

	while (true)
	{
		if (deref <= 0)
			break;
		ptr = *reinterpret_cast<T**>(ptr);
		--deref;
	}

	*out = ptr;
}

#endif