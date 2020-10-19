#include "pch.h"
#include "types.h"
#include "signatures.h"
#include "memory.h"
#include "reclass.h"
#include "functions.h"

TextInfo* m_text_info;
uint64_t* m_frame_count;
cnetwork_player_manager* m_network_manager;
cworld* m_pworld;
uint8_t* m_player_online;
fiveBytes* m_no_police;
MemoryPool** m_entity_pool;
cgta_time* m_time_struct;
cgame_version* m_game_version;
creplay_interface* m_replay_interface;
ccam_interface* m_camera;
Screen* m_resolution;
cviewport* m_view_port;

namespace ui
{
	tdraw_rect draw_rect;
	tset_text_entry set_text_entry;
	tadd_text_component_substring_player_name add_text_component_substring_player_name;
	tdraw_text draw_text;
}

namespace dlc
{
	tis_dlc_present is_dlc_present;
}

namespace streaming
{
	trequest_model request_model;
	thas_model_loaded has_model_loaded;
	tis_model_in_cdimage is_model_in_cdimage;
	tset_model_as_no_longer_needed set_model_as_no_longer_needed;
	trequest_anim_dict request_anim_dict;
	tget_model_data get_model_data;
}

namespace decorator
{
	tdecor_set_int decor_set_int;
}

namespace audio
{
	tset_mobile_radio_enabled_during_gameplay set_mobile_radio_enabled_during_gameplay;
	tget_player_radio_station_index get_player_radio_station_index;
}

namespace vehicle
{
	tcreate_vehicle create_vehicle;
	tset_vehicle_forward_speed set_vehicle_forward_speed;
	tis_player_pressing_horn is_player_pressing_horn;
	tset_vehicle_engine_on set_vehicle_engine_on;
	tset_vehicle_number_plate_text set_vehicle_number_plate_text;
	tset_vehicle_number_plate_index set_vehicle_number_plate_index;
	tset_vehicle_mod_kit set_vehicle_mod_kit;
	tset_vehicle_fixed set_vehicle_fixed;
	tset_vehicle_dirt_level set_vehicle_dirt_level;

	float get_vehicle_forward_speed(cvehicle* veh)
	{
		if (veh == nullptr)
			return 0.f;
		const v3 v3_speed = *veh->m_vtable->get_velocity(veh);
		return sqrt(pow(v3_speed.x, 2) + pow(v3_speed.y, 2) + pow(v3_speed.z, 2));
	}

}

namespace heading
{
	tfunc1 func1;
	tfunc2 func2;

	float get_entity_heading(int pedHandle)
	{
		const __int64 v1 = func1(pedHandle);
		if (!v1)
			return 0.f;
		const __int64 v2 = func2(v1);
		if (!v2)
			return 0.f;
		return Functions::rad_to_deg(atan2f(*(float*)(v2 + 0x64), *(float*)(v2 + 0x74)));
	}
}

namespace utility
{
	taddress_to_handle address_to_handle;
	thandle_to_address handle_to_address;

	uintptr_t get_address_of_item_in_pool(MemoryPool* pool, const int handle)
	{
		if (pool == nullptr)
			return 0;
		const auto index = handle >> 8;
		const int  flag = pool->bool_adr[index];

		if (flag & 0x80 || flag != (handle & 0xFF))
			return 0;
		return pool->list_addr + index * pool->item_size;
	}
}

namespace ped
{
	ttask_warp_ped_into_vehicle task_warp_ped_into_vehicle;
}

namespace game_controls
{
	tis_control_pressed is_control_pressed;
	tdisable_control_action disable_control_action;
	tis_control_just_pressed is_control_just_pressed;
}


bool initialiseSignatures()
{
	dlc::is_dlc_present = reinterpret_cast<dlc::tis_dlc_present>(CPattern("\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x81\xF9\x00\x00\x00\x00", "xxxx?xxxxxxx????").find(0).get(0).get<char>(0, "is_dlc_present"));

	ui::draw_rect = reinterpret_cast<ui::tdraw_rect>(CPattern("\x48\x8B\xC4\x48\x89\x58\x08\x57\x48\x83\xEC\x70\x48\x63\x0D\x00\x00\x00\x00\x0F", "xxxxxxxxxxxxxxx????x").find(0).get(0).get<char>(0, "draw_rect"));
	ui::set_text_entry = reinterpret_cast<ui::tset_text_entry>(CPattern("\x48\x83\xEC\x28\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x33\xC9\x48\x85\xC0", "xxxxx????x????xxxxx").find(0).get(0).get<char>(0, "set_text_entry"));
	ui::add_text_component_substring_player_name = reinterpret_cast<ui::tadd_text_component_substring_player_name>(CPattern("\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x20\x8B\x05\x00\x00\x00\x00\x4C\x8B\xD1", "xxxx?xxxx?xxxx?xxxxxxx????xxx").find(0).get(0).get<char>(0, "add_text_component_substring_player_name"));
	ui::draw_text = reinterpret_cast<ui::tdraw_text>(CPattern("\x40\x53\x48\x83\xEC\x40\x0F\x29\x74\x24\x00\x0F\x29\x7C\x24\x00\x41\x8B\xD8", "xxxxxxxxxx?xxxx?xxx").find(0).get(0).get<char>(0, "draw_text"));

	streaming::request_model = reinterpret_cast<streaming::trequest_model>(CPattern("\x48\x89\x5C\x24\x00\x48\x89\x7C\x24\x00\x55\x48\x8B\xEC\x48\x83\xEC\x50\x8B\x45\x18", "xxxx?xxxx?xxxxxxxxxxx").find(0).get(0).get<char>(0, "request_model"));
	streaming::has_model_loaded = reinterpret_cast<streaming::thas_model_loaded>(CPattern("\x48\x89\x7C\x24\x00\x55\x48\x8B\xEC\x48\x83\xEC\x20\x8B\x45\x18\xBF", "xxxx?xxxxxxxxxxxx").find(0).get(0).get<char>(0, "has_model_loaded"));
	streaming::is_model_in_cdimage = reinterpret_cast<streaming::tis_model_in_cdimage>(CPattern("\x48\x83\xEC\x28\x8B\x44\x24\x38\x48\x8D\x54\x24\x00\xC7\x44\x24\x00\x00\x00\x00\x00\x0D\x00\x00\x00\x00\x25\x00\x00\x00\x00\x89\x44\x24\x38\xE8\x00\x00\x00\x00\x0F\xB7\x44\x24\x00\x66\x89\x44\x24\x00\x8B\x44\x24\x38\x0D\x00\x00\x00\x00\x0F\xBA\xF0\x1C\x89\x44\x24\x38", "xxxxxxxxxxxx?xxx?????x????x????xxxxx????xxxx?xxxx?xxxxx????xxxxxxxx").find(0).get(0).get<char>(0, "is_model_in_cdimage"));
	streaming::set_model_as_no_longer_needed = reinterpret_cast<streaming::tset_model_as_no_longer_needed>(CPattern("\x40\x53\x48\x83\xEC\x30\x48\x8D\x54\x24\x00\x8B\xD9", "xxxxxxxxxx?xx").find(0).get(0).get<char>(0, "set_model_as_no_longer_needed"));
	streaming::request_anim_dict = reinterpret_cast<streaming::trequest_anim_dict>(CPattern("\x48\x83\xEC\x58\x48\x8B\xD1\x33\xC9", "xxxxxxxxx").find(0).get(0).get<char>(0, "request_anim_dict"));
	streaming::get_model_data = reinterpret_cast<streaming::tget_model_data>(CPattern("\x0F\xB7\x05\x00\x00\x00\x00\x45\x33\xC9\x4C\x8B\xDA\x66\x85\xC0\x0F\x84\x00\x00\x00\x00\x44\x0F\xB7\xC0\x33\xD2\x8B\xC1\x41\xF7\xF0\x48\x8B\x05\x00\x00\x00\x00\x4C\x8B\x14\xD0\xEB\x09\x41\x3B\x0A\x74\x54", "xxx????xxxxxxxxxxx????xxxxxxxxxxxxxx????xxxxxxxxxxx").find(0).get(0).get<char>(0, "get_model_data"));

	decorator::decor_set_int = reinterpret_cast<decorator::tdecor_set_int>(CPattern("\x48\x89\x5C\x24\x00\x44\x89\x44\x24\x00\x57\x48\x83\xEC\x20\x48\x8B\xFA\xE8\x00\x00\x00\x00\x48\x8B\xD8\x48\x85\xC0\x74\x22\x48\x8B\xD7\x33\xC9\xE8\x00\x00\x00\x00\x4C\x8D\x44\x24\x00\x48\x8D\x54\x24\x00\x48\x8B\xCB\x89\x44\x24\x48\xE8\x00\x00\x00\x00\xB0\x01", "xxxx?xxxx?xxxxxxxxx????xxxxxxxxxxxxxx????xxxx?xxxx?xxxxxxxx????xx").find(0).get(0).get<char>(0, "decor_set_int"));

	audio::set_mobile_radio_enabled_during_gameplay = reinterpret_cast<audio::tset_mobile_radio_enabled_during_gameplay>(CPattern("\x40\x53\x48\x83\xEC\x20\x8A\xD9\x48\x8D\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x48\x8D\x0D\x00\x00\x00\x00\x8B\xD0\xE8\x00\x00\x00\x00\x48\x85\xC0\x74\x10", "xxxxxxxxxxx????x????xxx????xxx????xxxxx").find(0).get(0).get<char>(0, "set_mobile_radio_enabled_during_gameplay"));
	audio::get_player_radio_station_index = reinterpret_cast<audio::tget_player_radio_station_index>(CPattern("\x48\x83\xEC\x28\x48\x8D\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x48\x85\xC0\x74\x0C", "xxxxxxx????x????xxxxx").find(0).get(0).get<char>(0, "get_player_radio_station_index"));

	vehicle::create_vehicle = reinterpret_cast<vehicle::tcreate_vehicle>(CPattern("\x48\x89\x5C\x24\x00\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8B\xEC\x48\x83\xEC\x50\xF3\x0F\x10\x02", "xxxx?xxxxxxxxxxxxxxxxxxxxxx").find(0).get(0).get<char>(0, "create_vehicle"));
	vehicle::set_vehicle_forward_speed = reinterpret_cast<vehicle::tset_vehicle_forward_speed>(CPattern("\x48\x83\xEC\x38\x0F\x29\x74\x24\x00\x0F\x28\xF1\xE8\x00\x00\x00\x00\x48\x85\xC0\x74\x2A\xF6\x40\x29\x01\x74\x19\xF3\x0F\x11\xB0\x00\x00\x00\x00\x80\x88\x00\x00\x00\x00\x00\x0F\x28\x74\x24\x00\x48\x83\xC4\x38\xC3\x0F\x28\xCE\x48\x8B\xC8\xE8\x00\x00\x00\x00", "xxxxxxxx?xxxx????xxxxxxxxxxxxxxx????xx?????xxxx?xxxxxxxxxxxx????").find(0).get(0).get<char>(0, "set_vehicle_forward_speed"));
	vehicle::set_vehicle_engine_on = reinterpret_cast<vehicle::tset_vehicle_engine_on>(CPattern("\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x20\x41\x8A\xE9\x41\x8A\xF8", "xxxx?xxxx?xxxx?xxxxxxxxxxx").find(0).get(0).get<char>(0, "set_vehicle_engine_on"));
	vehicle::set_vehicle_number_plate_text = reinterpret_cast<vehicle::tset_vehicle_number_plate_text>(CPattern("\x40\x53\x48\x83\xEC\x20\x48\x8B\xDA\xE8\x00\x00\x00\x00\x48\x85\xC0\x74\x10\x48\x8B\x48\x48", "xxxxxxxxxx????xxxxxxxxx").find(0).get(0).get<char>(0, "set_vehicle_number_plate_text"));
	//vehicle::set_vehicle_number_plate_index = reinterpret_cast<vehicle::tset_vehicle_number_plate_index>(CPattern("\x83\xFA\xFF\x0F\x8C\x00\x00\x00\x00\x48\x8B", "xxxxx????xx").find(0).get(0).get<char>(0, "set_vehicle_number_plate_index"));
	//vehicle::set_vehicle_mod_kit = reinterpret_cast<vehicle::tset_vehicle_mod_kit>(CPattern("\x40\x53\x48\x83\xEC\x20\x8B\xDA\xE8\x00\x00\x00\x00\x48\x85\xC0\x74\x27","xxxxxxxxx????xxxxx").find(0).get(0).get<char>(0, "set_vehicle_mod_kit"));
	vehicle::set_vehicle_fixed = reinterpret_cast<vehicle::tset_vehicle_fixed>(CPattern("\x40\x53\x48\x83\xEC\x20\xE8\x00\x00\x00\x00\x48\x8B\xD8\x48\x85\xC0\x74\x28\x4C\x8B\x10", "xxxxxxx????xxxxxxxxxxx").find(0).get(0).get<char>(0, "set_vehicle_fixed"));
	//vehicle::is_player_pressing_horn = reinterpret_cast<vehicle::tis_player_pressing_horn>(CPattern("\x48\x83\xEC\x28\xB2\x01\xE8\x00\x00\x00\x00\x48\x85\xC0\x75\x05\x48\x83\xC4\x28\xC3\x48\x8B\x88\x00\x00\x00\x00\x48\x83\xC4\x28\xE9\x00\x00\x00\x00\x90\x48\x8B\x48\x89", "xxxxxxx????xxxxxxxxxxxxx????xxxxx????xxxxx").find(0).get(0).get<char>(0, "is_player_pressing_horn"));
	vehicle::set_vehicle_dirt_level = reinterpret_cast<vehicle::tset_vehicle_dirt_level>(CPattern("\x48\x83\xEC\x38\x0F\x29\x74\x24\x00\x0F\x28\xF1\xE8\x00\x00\x00\x00\x48\x85\xC0\x74\x1A\x0F\x2F\x35\x00\x00\x00\x00", "xxxxxxxx?xxxx????xxxxxxxx????").find(0).get(0).get<char>(0, "set_vehicle_dirt_level"));

	ped::task_warp_ped_into_vehicle = reinterpret_cast<ped::ttask_warp_ped_into_vehicle>(CPattern("\x48\x8B\xC4\x48\x89\x58\x08\x48\x89\x68\x10\x48\x89\x70\x18\x48\x89\x78\x20\x41\x56\x48\x83\xEC\x20\x44\x8B\xF1\x8B\xCA\x41\x8B\xD8", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx").find(0).get(0).get<char>(0, "test"));

	heading::func1 = reinterpret_cast<heading::tfunc1>(CPattern("\x40\x53\x48\x83\xEC\x20\xE8\x00\x00\x00\x00\x48\x8B\xD8\x48\x85\xC0\x74\x19\x4C\x8B\x00\x8B\x15\x00\x00\x00\x00\x48\x8B\xC8\x41\xFF\x50\x08\x84\xC0\x74\x05\x48\x8B\xC3\xEB\x02\x33\xC0\x48\x83\xC4\x20\x5B\xC3\x40\x53\x48\x83\xEC\x20\xE8\x00\x00\x00\x00\x48\x8B\xD8", "xxxxxxx????xxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxx").find(0).get(0).get<char>(0, "func1"));
	heading::func2 = reinterpret_cast<heading::tfunc2>(CPattern("\x48\x8B\xC1\x48\x85\xC9\x74\x22", "xxxxxxxx").find(0).get(0).get<char>(0, "func2"));

	utility::address_to_handle = reinterpret_cast<utility::taddress_to_handle>(CPattern("\x48\x89\x5C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x20\x8B\x15\x00\x00\x00\x00\x48\x8B\xF9\x48\x83\xC1\x10\x33\xDB", "xxxx?xxxx?xxxxxxx????xxxxxxxxx").find(0).get(0).get<char>(0, "address_to_handle"));
	utility::handle_to_address = reinterpret_cast<utility::thandle_to_address>(CPattern("\x83\xF9\xFF\x74\x31\x4C\x8B\x0D\x00\x00\x00\x00", "xxxxxxxx????").find(0).get(0).get<char>(0, "handle_to_address"));

	game_controls::is_control_pressed = reinterpret_cast<game_controls::tis_control_pressed>(CPattern("\x40\x53\x48\x83\xEC\x20\x8B\xDA\x85\xC9\x75\x09\xB1\x01\xE8\x00\x00\x00\x00\xEB\x0C\x83\xF9\x01\xB1\x01\x74\xF2\xE8\x00\x00\x00\x00\x8B\xD3\x48\x8B\xC8\xE8\x00\x00\x00\x00\x4C\x8D\x05\x00\x00\x00\x00\xF3\x0F\x10\x0D\x00\x00\x00\x00\x48\x8B\xC8\x48\x83\xC4\x20", "xxxxxxxxxxxxxxx????xxxxxxxxxx????xxxxxx????xxx????xxxx????xxxxxxx").find(3).get(2).get<char>(0, "is_control_pressed"));
	game_controls::disable_control_action = reinterpret_cast<game_controls::tdisable_control_action>(CPattern("\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x20\x41\x8A\xF0\x8B\xDA\x8B\xF9", "xxxx?xxxx?xxxx?xxxxxxxxxxxx").find(0).get(0).get<char>(0, "disable_control_action"));
	game_controls::is_control_just_pressed = reinterpret_cast<game_controls::tis_control_just_pressed>(CPattern("\x40\x53\x48\x83\xEC\x20\x8B\xDA\x85\xC9\x75\x09\xB1\x01\xE8\x00\x00\x00\x00\xEB\x0C\x83\xF9\x01\xB1\x01\x74\xF2\xE8\x00\x00\x00\x00\x8B\xD3\x48\x8B\xC8\xE8\x00\x00\x00\x00\x4C\x8D\x05\x00\x00\x00\x00\xF3\x0F\x10\x0D\x00\x00\x00\x00\x48\x8B\xC8\x48\x83\xC4\x20", "xxxxxxxxxxxxxxx????xxxxxxxxxx????xxxxxx????xxx????xxxx????xxxxxxx").find(0).get(0).get<char>(0, "is_control_just_pressed"));


	set_pattern<TextInfo>("TextInfo", "\x48\x8D\x05\x00\x00\x00\x00\x48\x89\x44\x24\x00\x8B\x05\x00\x00\x00\x00\x89\x44\x24\x28", "xxx????xxxx?xx????xxxx", &m_text_info, true, 3, 0, 0);
	set_pattern<uint64_t>("frame count", "\x8B\x15\x00\x00\x00\x00\x41\xFF\xCF", "xx????xxx", &m_frame_count, true, 2, 0, 0);
	set_pattern<cnetwork_player_manager>("network manager", "\x48\x8B\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x48\x8B\xC8\xE8\x00\x00\x00\x00\x48\x8B\xCF", "xxx????x????xxxx????xxx", &m_network_manager, true, 3, 1, 0);
	set_pattern<cworld>("world", "\x48\x8B\x05\x00\x00\x00\x00\x4C\x8B\x68\x08\x4C\x89\xAD\xD8\x03\x00\x00\x4D\x85\xED\x0F\x84\x93\x04\x00\x00\x8D\x4B\x0F\x48\x8D", "xxx????xxxxxxxxxxxxxxxxxxxxxxxxx", &m_pworld, true, 3, 1, 0);
	set_pattern<uint8_t>("player online", "\x40\x38\x35\x00\x00\x00\x00\x74\x0A\x48\x8B\xCF", "xxx????xxxxx", &m_player_online, true, 3, 0, 0);
	set_pattern<fiveBytes>("no_police", "\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x48\x89\x74\x24\x00\x57\x41\x56\x41\x57\x48\x83\xEC\x30\x8B\x05\x00\x00\x00\x00\x8B\xB9\x00\x00\x00\x00", "xxxx?xxxx?xxxx?xxxxxxxxxxx????xx????", &m_no_police, false, 0, 0, 0);
	set_pattern<MemoryPool*>("entity pool", "\x4C\x8B\x0D\x00\x00\x00\x00\x44\x8B\xC1\x49\x8B\x41\x08", "xxx????xxxxxxx", &m_entity_pool, true, 3, 0, 0);
	set_pattern<cgta_time>("time struct", "\x48\x8D\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x8B\x05\x00\x00\x00\x00\x66\x0F\x6E\x0D\x00\x00\x00\x00", "xxx????x????xx????xxxx????", &m_time_struct, true, 3, 0, 0);
	set_pattern<cgame_version>("version struct", "\x4C\x8D\x05\x00\x00\x00\x00\x48\x8D\x15\x00\x00\x00\x00\x48\x8B\xC8\xE8\x00\x00\x00\x00\x48\x8D\x15\x00\x00\x00\x00\x48\x8D\x4C\x24\x00\xE8\x00\x00\x00\x00\x85\xC0\x75\x20\xB2\x01\x48\x8B\xCF\xE8\x00\x00\x00\x00\x4C\x8D\x05\x00\x00\x00\x00\x48\x8D\x15\x00\x00\x00\x00", "xxx????xxx????xxxx????xxx????xxxx?x????xxxxxxxxxx????xxx????xxx????", &m_game_version, true, 3, 0, 0);
	set_pattern<creplay_interface>("replay interface", "\x48\x8D\x0D\x00\x00\x00\x00\x48\x8B\xD7\xE8\x00\x00\x00\x00\x48\x8D\x0D\x00\x00\x00\x00\x8A\xD8\xE8\x00\x00\x00\x00\x84\xDB\x75\x13\x48\x8D\x0D\x00\x00\x00\x00", "xxx????xxxx????xxx????xxx????xxxxxxx????", &m_replay_interface, true, 3, 1, 0);
	set_pattern<ccam_interface>("camera struct", "\x48\x8B\x05\x00\x00\x00\x00\x4A\x8B\x1C\xF0", "xxx????xxxx", &m_camera, true, 3, 1, 0);
	set_pattern<Screen>("resolution", "\x8B\x0D\x00\x00\x00\x00\x49\x8D\x56\x28", "xx????xxxx", &m_resolution, true, 2, 0, 0);
	set_pattern<cviewport>("viewport", "\x48\x8B\x15\x00\x00\x00\x00\x48\x8D\x2D\x00\x00\x00\x00\x48\x8B\xCD", "xxx????xxx????xxx", &m_view_port, true, 3, 1, 0);

	return SUCCESS;
}