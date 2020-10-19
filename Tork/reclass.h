#pragma once
#ifndef __RECLASS_H__
#define __RECLASS_H__

#include "types.h"

#pragma pack(push, 1)
// Generated using ReClass 2016
#define is_valid_ptr(x) (x != nullptr)

class cworld;
class cped;
class centity;
class cnavigation;
class cvehicle;
class cdraw_handler;
class chandling_data;
class cplayer_info;
class cped_inventory;
class cweapon_manager;
class cnetwork_player_manager;
class cnetwork_bandwith_manager;
class cnet_game_player;
class cweapon_info;
class cammo_info;
class cammo_wrap;
class cammo;
class cstream_render_gfx;
class ccustom_shader_effects;
class ccolour;
class creplay_interface;
class creplay_interface_vehicle;
class creplay_interface_ped;
class creplay_interface_pickup;
class creplay_interface_object;
class ccurrent_ped_cam;
class ccamera_meta_data;
class ccam_interface;
class ccam_gameplay_director;
class cattacker;
class cwater_quads;
class cwater_data;
class cvehicle_list;
class cvehicle_handle;
class cped_list;
class cped_handle;
class cmodel_info;
class centity_vtable;
class cped_factory_vtable;
class cnet_object_entity;
class ccdimage;
class cmodels;
class cmodel;
class cviewport;
class cblip;
class cbliplist;
class cwaypoint;
class cgta_time;
class cgame_version;



struct net_game_event_vtable
{
	char pad_0000[0x08];
	char* (*get_name)();
	char pad_0010[0x28];
	uint8_t(*execute)(struct net_game_event* event_data, struct net_game_player* sender, uint64_t a3);
};

struct net_game_event
{
	struct net_game_event_vtable* vtable;
	uint16_t id;
	char pad_000a[0x0E];
	struct net_game_player* recipient;
	char pad_0020[0x08];
};

struct report_cash_spawn_event
{
	struct net_game_event base;
	char pad_0028[0x10];
	uint32_t value;
	uint32_t hash;
};

struct update_fxn_event
{
	struct net_game_event base;
	char pad_0028[0x08];
	uint32_t flag;
};

struct increment_stat_event
{
	struct net_game_event base;
	char pad_0028[0x08];
	uint32_t hash;
	uint32_t value;
};

struct game_weather_event
{
	struct net_game_event base;
	char pad_0028[0x08];
	struct net_game_player* net_player;
	char server;
	char pad_0039[0x03];
	int weather_id;
};

struct game_clock_event
{
	struct net_game_event base; // 0x28
	char pad_0028[0x08]; // 0x30
	struct net_game_player* net_player; // 0x38
	char pad_0038[0x18]; // 0x50
	int time;
};

struct alter_wanted_level
{
	struct net_game_event base; // 0x28
	char pad_0028[0x08]; // 0x30
	net_game_player* net_player; // 0x38
	char pad_0038[0x08]; // 0x40
	int wanted_level; // 0x44
	int a4; // 0x48
	char pad_0044[0x01]; // 0x49
	char a5; // 0x4A

};

struct explosion_event
{
	struct net_game_event base;
	//char pad_0028[0x2C];
	char pad_0028[0x18];
	float x;
	float y;
	float z;
};

class cworld
{
public:
	cped_factory_vtable* m_vtable; //0x0000 
	cped* m_local_ped; //0x0008 
}; //Size=0x0010

class centity
{
public:
	centity_vtable* m_vtable; //0x0000 
	char m_pad_0x0008[0x18]; //0x0008
	cmodel_info* m_model_info; //0x0020 
	uint8_t m_type; //0x0028 
	char m_pad_0x0029[0x3]; //0x0029
	uint8_t m_invisible; //0x002C 
	char m_pad_0x002D[0x2]; //0x002D
	uint8_t m_respawn; //0x002F 
	cnavigation* m_navigation; //0x0030 
	char m_pad_0x0038[0x10]; //0x0038
	cdraw_handler* m_draw_handler; //0x0048 
	char m_pad_0x0050[0x40]; //0x0050
	v3 m_visual_position; //0x0090 
	char m_pad_0x009C[0x34]; //0x009C
	cnet_object_entity* m_net_object_entity; //0x00D0 
	uint8_t m_state; //0x00D8 
	char m_pad_0x00D9[0xAF]; //0x00D9
	entity_proofs m_entity_proofs; //0x0188 
	char m_pad_0x018C[0x4]; //0x018C
	uint8_t m_entity_proofs_2; //0x0190 
	char m_pad_0x0191[0xEF]; //0x0191
	float m_health; //0x0280 
	char m_pad_0x0284[0x1C]; //0x0284
	float m_max_health; //0x02A0 
	char m_pad_0x02A4[0x4]; //0x02A4
	cattacker* m_attacker; //0x02A8 
}; //Size=0x02B0

class cped : public centity
{
public:
	char m_pad_0x02B0[0xA78]; //0x02B0
	cvehicle* m_latest_vehicle; //0x0D28 
	char m_pad_0x0D30[0x378]; //0x0D30
	uint8_t m_no_ragdoll; //0x10A8 
	char m_pad_0x10A9[0xF]; //0x10A9
	cplayer_info* m_player_info; //0x10B8 
	cped_inventory* m_inventory; //0x10C0 
	cweapon_manager* m_weapon_manager; //0x10C8 
	char m_pad_0x10D0[0x31C]; //0x10D0
	uint8_t m_seat_belt; //0x13EC 
	char m_pad_0x13ED[0xB]; //0x13ED
	uint8_t m_wind_shield; //0x13F8 
	char m_pad_0x13F9[0x1]; //0x13F9
	uint8_t m_cant_switch_weapons; //0x13FA 
	uint8_t m_activity; //0x13FB 
	char m_pad_0x13FC[0x6F]; //0x13FC
	uint8_t m_not_in_vehicle; //0x146B 
	char m_pad_0x146C[0x4C]; //0x146C
	float m_armour; //0x14B8 

	bool inVehicle()
	{
		return !m_not_in_vehicle;
	}
}; //Size=0x14BC


class cnavigation
{
public:
	char m_pad_0x0000[0x20]; //0x0000
	float m_heading1; //0x0020 
	float m_heading2; //0x0024 
	char m_pad_0x0028[0x8]; //0x0028
	v3 m_rotation; //0x0030 
	char m_pad_0x003C[0x14]; //0x003C
	v3 m_position; //0x0050 
}; //Size=0x005C

class cvehicle : public centity
{
public:
	char m_pad_0x02B0[0x70]; //0x02B0
	float m_rocket_energy; //0x0320 
	char m_pad_0x0324[0x4D0]; //0x0324
	float m_fuel_level; //0x07F4 
	char m_pad_0x07F8[0x38]; //0x07F8
	uint8_t m_cur_gear; //0x0830 
	char m_pad_0x0831[0x1]; //0x0831
	uint8_t m_cur_gear2; //0x0832 
	char m_pad_0x0833[0x1]; //0x0833
	int16_t m_unknown; //0x0834 
	uint8_t m_top_gear; //0x0836 
	char m_pad_0x0837[0x91]; //0x0837
	chandling_data* m_handling_data; //0x08C8 
	char m_pad_0x08D0[0x4]; //0x08D0
	int m_visibly_damagable; //0x08D4 
	char m_pad_0x08D5[0xB3]; //0x08D5
	float m_dirt_level; //0x0988 
	char m_pad_0x098C[0x1F4]; //0x098C
	uint8_t m_visually_openable_doors; //0x0B80 
	char m_pad_0x0B81[0x4B]; //0x0B81
	float m_gravity; //0x0BCC 
	uint8_t m_max_passengers; //0x0BD0 
	char m_pad_0x0BD1[0x1]; //0x0BD1
	uint8_t m_num_passengers; //0x0BD2 
	char m_pad_0x0BD3[0x1]; //0x0BD3
}; //Size=0x0BD4

class cdraw_handler
{
public:
	char m_pad_0x0000[0x20]; //0x0000
	ccustom_shader_effects* m_shader_effects; //0x0020 
	char m_pad_0x0028[0x348]; //0x0028
	cstream_render_gfx* N00000F6F; //0x0370 
	char m_pad_0x0378[0x38]; //0x0378
	uint8_t m_tire_tuning; //0x03B0 
	uint8_t N00001050; //0x03B1 
	uint8_t m_spoiler; //0x03B2 
	uint8_t m_front_bumper; //0x03B3 
	uint8_t m_rear_bumper; //0x03B4 
	uint8_t m_skirt; //0x03B5 
	uint8_t m_exaust; //0x03B6 
	uint8_t m_roll_cage; //0x03B7 
	uint8_t N00000F78; //0x03B8 
	uint8_t m_hood; //0x03B9 
	char m_pad_0x03BA[0x2]; //0x03BA
	uint8_t m_roof; //0x03BC 
	char m_pad_0x03BD[0x19]; //0x03BD
	uint8_t m_engine; //0x03D6 
	uint8_t m_brakes; //0x03D7 
	uint8_t m_transmission; //0x03D8 
	uint8_t m_horn; //0x03D9 
	uint8_t m_suspension; //0x03DA 
	uint8_t m_armour; //0x03DB 
	char m_pad_0x03DC[0x1]; //0x03DC
	uint8_t m_turbo; //0x03DD 
	char m_pad_0x03DE[0x2]; //0x03DE
	uint8_t N00000F7C; //0x03E0 
	uint8_t m_headlights; //0x03E1 
	uint8_t m_tire_index; //0x03E2 
	char m_pad_0x03E3[0xD]; //0x03E3
	uint8_t N00000F7F; //0x03F0 
	uint8_t N00001095; //0x03F1 
	uint8_t N00001099; //0x03F2 
	uint8_t m_fenders; //0x03F3 
	char m_pad_0x03F4[0x1]; //0x03F4
	uint8_t N00001096; //0x03F5 
	uint8_t m_primary_colour; //0x03F6 
	uint8_t m_secondary_colour; //0x03F7 
	uint8_t m_pearlescent; //0x03F8 
	uint8_t m_wheel_colour; //0x03F9 
	char m_pad_0x03FA[0x2]; //0x03FA
	uint8_t m_tire_colour_red; //0x03FC 
	uint8_t m_tire_colour_green; //0x03FD 
	uint8_t m_tire_colour_blue; //0x03FE 
	uint8_t m_window_tint; //0x03FF 
	int16_t N000010AF; //0x0400 
	uint8_t m_neon_light_left; //0x0402 
	uint8_t m_neon_light_right; //0x0403 
	uint8_t m_neon_light_front; //0x0404 
	uint8_t m_neon_light_back; //0x0405 
	char m_pad_0x0406[0x2A]; //0x0406
}; //Size=0x0430

class chandling_data
{
public:
	char m_pad_0x0000[0xC]; //0x0000
	float m_mass; //0x000C 
	char m_pad_0x0010[0x14]; //0x0010
	v3 m_centre_of_mass_offset; //0x0024 
	v3 m_inertia_multiplier; //0x0030 
	char m_pad_0x003C[0x4]; //0x003C
	float m_percent_submerged; //0x0040 
	char m_pad_0x0044[0x8]; //0x0044
	float m_acceleration; //0x004C 
	char m_pad_0x0050[0x4]; //0x0050
	float m_drive_inertia; //0x0054 
	float m_clutch_scale_up_rate; //0x0058 
	float m_clutch_scale_down_rate; //0x005C 
	float m_initial_drive_force; //0x0060 
	char m_pad_0x0064[0x8]; //0x0064
	float m_brake_force; //0x006C 
	char m_pad_0x0070[0x4]; //0x0070
	float m_brake_bias_front; //0x0074 
	char m_pad_0x0078[0x4]; //0x0078
	float m_hand_brake_foce; //0x007C 
	char m_pad_0x0080[0x8]; //0x0080
	float m_traction_curve_max; //0x0088 
	char m_pad_0x008C[0x4]; //0x008C
	float m_traction_curve_min; //0x0090 
	char m_pad_0x0094[0xC]; //0x0094
	float m_traction_spring_delta_max; //0x00A0 
	char m_pad_0x00A4[0x4]; //0x00A4
	float m_low_speed_traction_loss_multiplier; //0x00A8 
	float m_camber_stiffness; //0x00AC 
	float m_traction_bias_front; //0x00B0 
	char m_pad_0x00B4[0x8]; //0x00B4
	float m_suspension_force; //0x00BC 
	float m_suspension_comp_damp; //0x00C0 
	float m_suspension_upper_limit; //0x00C4 
	float m_suspension_lower_limit; //0x00C8 
	char m_pad_0x00CC[0xC]; //0x00CC
	float m_anti_roll_bar_force; //0x00D8 
	char m_pad_0x00DC[0xC]; //0x00DC
	float m_roll_centre_height_front; //0x00E8 
	float m_roll_centre_height_rear; //0x00EC 
	float m_collision_damage_multiplier; //0x00F0 
	float m_weapon_damage_multiplier; //0x00F4 
	float m_deformation_damage_multiplier; //0x00F8 
	float m_engine_damage_multiplier; //0x00FC 
	float m_petrol_tank_volume; //0x0100 
	float m_oil_tank_volume; //0x0104 
	char m_pad_0x0108[0x4]; //0x0108
	float m_seat_offset_dist_x; //0x010C 
	float m_seat_offset_dist_y; //0x0110 
	float m_seat_offset_dist_z; //0x0114 
	int32_t m_montary_value; //0x0118 
}; //Size=0x011C

class cplayer_info
{
public:
	char m_pad_0x0000[0x34]; //0x0000
	ip_address m_internal_ip; //0x0034 
	int16_t m_internal_port; //0x0038 
	char m_pad_0x003A[0x2]; //0x003A
	ip_address m_relay_ip; //0x003C 
	int16_t m_relay_port; //0x0040 
	char m_pad_0x0042[0x2]; //0x0042
	ip_address m_external_ip; //0x0044 
	int16_t m_external_port; //0x0048 
	char m_pad_0x004A[0x32]; //0x004A
	char m_name[0x14]; //0x007C 
	char m_pad_0x0090[0x4]; //0x0090
	int32_t m_team; //0x0094 
	char m_pad_0x0098[0xB0]; //0x0098
	float m_swim_speed_multiplier; //0x0148 
	float m_run_speed_multiplier; //0x014C 
	char m_pad_0x0150[0x78]; //0x0150
	cped* m_player_ped; //0x01C8 
	char m_pad_0x01D0[0x29]; //0x01D0
	uint8_t m_frame_flags; //0x01F9 
	char m_pad_0x01FA[0x61E]; //0x01FA
	uint8_t m_wanted_level; //0x0818 
	char m_pad_0x0819[0x47F]; //0x0819
	float m_unknown_multiplier_1; //0x0C98 
	float m_unknown_multiplier_2; //0x0C9C 
	float m_unknown_multiplier_3; //0x0CA0 
	float m_melee_weapon_damage_multiplier; //0x0CA4 
	float m_melee_damage_multiplier; //0x0CA8 
}; //Size=0x0CAC

class cped_inventory
{
public:
	char m_pad_0x0000[0x8]; //0x0000
}; //Size=0x0008

class cweapon_manager
{
public:
	char m_pad_0x0000[0x20]; //0x0000
	cweapon_info* m_weapon_info; //0x0020 
}; //Size=0x0028

class cnetwork_player_manager
{
public:
	char m_pad_0x0000[0x10]; //0x0000
	cnetwork_bandwith_manager* m_bandwidth_manager; //0x0010 
	char m_pad_0x0018[0xD0]; //0x0018
	cnet_game_player* m_local_player; //0x00E8 
	char m_pad_0x00F0[0x88]; //0x00F0
	uint8_t m_players_online; //0x0178 
	char m_pad_0x0179[0x7]; //0x0179
	cnet_game_player* m_players[0x20]; //0x0180 
}; //Size=0x0280

class cnetwork_bandwith_manager
{
public:
	char m_pad_0x0000[0x8]; //0x0000
}; //Size=0x0008

class cnet_game_player
{
public:
	char m_pad_0x0000[0x2D]; //0x0000
	uint8_t m_player_id; //0x002D 
	char m_pad_0x002E[0x7A]; //0x002E
	cplayer_info* m_player_info; //0x00A8 
	char m_pad_0x00B0[0xF1]; //0x00B0
	uint8_t m_rockstar_dev; //0x01A1 
	char m_pad_0x01A2[0x92]; //0x01A2
	uint32_t m_cheat_flag_0; //0x0234 
	char m_pad_0x0238[0x2C]; //0x0238
	uint32_t m_cheat_flag_1; //0x0264 
}; //Size=0x0268

class cweapon_info
{
public:
	char m_pad_0x0000[0x10]; //0x0000
	uint32_t m_name_hash; //0x0010 
	uint32_t m_model_hash; //0x0014 
	char m_pad_0x0018[0x48]; //0x0018
	cammo_info* m_ammo_info; //0x0060 
	char m_pad_0x0068[0xC]; //0x0068
	float m_accuracy_spread; //0x0074 
	float m_accurate_mode_accuracy_modifier; //0x0078 
	float m_run_and_gun_accuracy_modifier; //0x007C 
	float m_run_and_gun_accuracy_min_override; //0x0080 
	float m_recoil_accuracy_max; //0x0084 
	float m_recoil_error_time; //0x0088 
	float m_recoil_recovery_rate; //0x008C 
	float m_recoil_accuracy_to_allow_headshot_ai; //0x0090 
	float m_min_headshot_distance_ai; //0x0094 
	float m_max_headshot_distance_ai; //0x0098 
	float m_headshot_damager_modifier_ai; //0x009C 
	float m_recoil_accuracy_to_allow_head_shot_player; //0x00A0 
	float m_min_head_shot_distance_player; //0x00A4 
	float m_max_head_shot_distance_player; //0x00A8 
	float m_head_shot_damage_modified_player; //0x00AC 
	float m_damage; //0x00B0 
	float m_damage_time; //0x00B4 
	float m_damage_time_in_vehicle; //0x00B8 
	float m_damage_time_in_vehicle_head_shot; //0x00BC 
	float m_hit_limbs_damage_modifier; //0x00C0 
	float m_network_hit_limbs_damage_modifier; //0x00C4 
	float m_lightlY_armoured_damage_modifier; //0x00C8 
	char m_pad_0x00CC[0x4]; //0x00CC
	float m_force_value; //0x00D0 
	float m_force_hit_ped; //0x00D4 
	float m_force_hit_vehicle; //0x00D8 
	float m_force_hit_flying_heli; //0x00DC 
	char m_pad_0x00E0[0x10]; //0x00E0
	float m_force_max_strength_multiplier; //0x00F0 
	float m_force_fall_off_range_start; //0x00F4 
	float m_force_fall_off_range_end; //0x00F8 
	float m_force_fall_off_min; //0x00FC 
	float m_projectile_force; //0x0100 
	float m_frag_impulse; //0x0104 
	float m_penetration; //0x0108 
	float m_vertical_launch_adjustment; //0x010C 
	float m_drop_forward_velocity; //0x0110 
	float m_speed; //0x0114 
	uint32_t m_bullets_in_batch; //0x0118 
	float m_batch_spread; //0x011C 
	float m_reload_time_mp; //0x0120 
	float m_reload_time_sp; //0x0124 
	float m_vehicle_reload_time; //0x0128 
	float m_anim_reload_rate; //0x012C 
	uint32_t m_bullets_per_anim_loop; //0x0130 
	float m_time_between_shots; //0x0134 
	float m_time_left_between_shots_where_should_fire_is_cached; //0x0138 
	float m_spin_up_time; //0x013C 
	float m_spin_down_time; //0x0140 
	char m_pad_0x0144[0x4]; //0x0144
	float m_alternate_wait_time; //0x0148 
	float m_bullet_bending_near_radius; //0x014C 
	float m_bullet_bending_far_radius; //0x0150 
	float m_bullet_bending_zoomed_radius; //0x0154 
	char m_pad_0x0158[0x34]; //0x0158
	float m_muzzle_smoke_fx_min_level; //0x018C 
	float m_muzzle_smoke_fx_inc_per_shot; //0x0190 
	float m_muzzle_smoke_fx_dec_per_shot; //0x0194 
	char m_pad_0x0198[0x28]; //0x0198
	float m_tracer_fx_chance_sp; //0x01C0 
	float m_tracer_fx_chance_mp; //0x01C4 
	float m_flash_fx_chance_sp; //0x01C8 
	float m_flash_fx_chance_mp; //0x01CC 
	float m_flash_fx_alt_chance; //0x01D0 
	float m_flash_fx_scale; //0x01D4 
	uint8_t m_flash_fx_light_enabled; //0x01D8 
	char m_pad_0x01D9[0x3]; //0x01D9
	uint8_t m_flash_fx_light_casts_shadows; //0x01DC 
	char m_pad_0x01DD[0x3]; //0x01DD
	v3 m_flash_fx_light_rgb_min; //0x01E0 
	char m_pad_0x01EC[0x4]; //0x01EC
	v3 m_flash_fx_light_rgb_max; //0x01F0 
	char m_pad_0x01FC[0x4]; //0x01FC
	v2 m_flash_fx_light_intensity_min_max; //0x0200 
	v2 m_flash_fx_light_range_min_max; //0x0208 
	v2 m_flash_fx_light_fall_off_min_max; //0x0210 
	uint8_t m_ground_disturb_fx_enabled; //0x0218 
	char m_pad_0x0219[0x3]; //0x0219
	float m_ground_disturb_fx_distance; //0x021C 
	char m_pad_0x0220[0x20]; //0x0220
	uint32_t m_initial_rumble_duration; //0x0240 
	float m_initial_rumble_intensity; //0x0244 
	float m_initial_rumble_intensity_trigger; //0x0248 
	uint32_t m_rumble_duration; //0x024C 
	float m_rumble_intensity; //0x0250 
	float m_rumble_intensity_trigger; //0x0254 
	float m_rumble_damage_intensity; //0x0258 
	uint32_t m_initial_rumble_duration_fps; //0x025C 
	float m_initial_rumble_intensity_fps; //0x0260 
	uint32_t m_rumble_duration_fps; //0x0264 
	float m_rumble_intensity_fps; //0x0268 
	float m_network_player_damage_modifier; //0x026C 
	float m_network_ped_damage_modifier; //0x0270 
	float m_network_head_shot_player_damage_modifier; //0x0274 
	float m_lock_on_range; //0x0278
	float m_weapon_range; //0x027C
	float m_ai_sound_range; //0x0280 
	float m_ai_potential_blast_event_range; //0x0284 
	float m_damage_fall_off_range_min; //0x0288 
	float m_damage_fall_off_range_max; //0x028C 
	char m_pad_0x0290[0x4]; //0x0290
	float m_damage_fall_off_modifier; //0x0294 
	char m_pad_0x0298[0x48]; //0x0298
	float m_camera_fov_value; //0x02E0 
	char m_pad_0x02E4[0x8]; //0x02E4
	float m_first_person_scope_fov; //0x02EC 
	char m_pad_0x02F0[0x20]; //0x02F0
	v3 m_first_person_rng_offset; //0x0310 
	char m_pad_0x031C[0x4]; //0x031C
	v3 m_first_person_rng_rotation_offset; //0x0320 
	char m_pad_0x032C[0x4]; //0x032C
	v3 m_first_person_lt_offset; //0x0330 
	char m_pad_0x033C[0x4]; //0x033C
	v3 m_first_person_lt_rotation_offset; //0x0340 
	char m_pad_0x034C[0x4]; //0x034C
	v3 m_first_person_scope_offset; //0x0350 
	char m_pad_0x035C[0x4]; //0x035C
	v3 m_first_person_scope_attachment_offset; //0x0360 
	char m_pad_0x036C[0x4]; //0x036C
	v3 m_first_person_scope_rotation_offset; //0x0370 
	char m_pad_0x037C[0x14]; //0x037C
	v3 m_first_as_third_person_idle_offset; //0x0390 
	char m_pad_0x039C[0x4]; //0x039C
	v3 m_first_as_third_person_rng_offset; //0x03A0 
	char m_pad_0x03AC[0x4]; //0x03AC
	v3 m_first_as_third_person_lt_offset; //0x03B0 
	char m_pad_0x03BC[0x4]; //0x03BC
	v3 m_first_as_third_person_scope_offset; //0x03C0 
	char m_pad_0x03CC[0x4]; //0x03CC
	v3 m_first_as_third_person_weapon_blocked_offset; //0x03D0 
	char m_pad_0x03DC[0x4]; //0x03DC
	float m_first_person_do_f_subject_magnification_power_near; //0x03E0 
	float m_first_person_do_f_max_near_in_focus_distance; //0x03E4 
	float m_first_person_do_f_max_near_in_focus_distance_blend_level; //0x03E8 
	char m_pad_0x03EC[0x14]; //0x03EC
	float m_zoom_factor_for_accurate_mode; //0x0400 
	char m_pad_0x0404[0xC]; //0x0404
	v3 m_aim_offset_min; //0x0410 
	char m_pad_0x041C[0x4]; //0x041C
	v3 m_aim_offset_max; //0x0420 
	char m_pad_0x042C[0x194]; //0x042C
	float m_aiming_breathing_additive_weight; //0x05C0 
	float m_firing_breathing_additive_weight; //0x05C4 
	float m_stealth_aiming_breathing_addative_weight; //0x05C8 
	float m_stealth_firing_breathing_addative_weight; //0x05CC 
	float m_aiming_lean_additive_weight; //0x05D0 
	float m_firing_lean_additive_weight; //0x05D4 
	float m_stealth_aiming_lean_additive_weight; //0x05D8 
	float m_stealth_firing_lean_additive_weight; //0x05DC 
	char* szWeaponName; //0x05E0
	char pad_05E8[40]; //0x05E8
}; //Size=0x05E0

class cammo_info
{
public:
	char m_pad_0x0000[0x8]; //0x0000
	cammo_wrap* m_ammo_wrap; //0x0008 
	char m_pad_0x0010[0x18]; //0x0010
	uint32_t m_max_ammo; //0x0028 
	char m_pad_0x002C[0x4]; //0x002C
}; //Size=0x0030

class cammo_wrap
{
public:
	cammo* m_ammo; //0x0000 
}; //Size=0x0008

class cammo
{
public:
	char m_pad_0x0000[0x18]; //0x0000
	uint32_t m_ammo; //0x0018 
	char m_pad_0x001C[0x4]; //0x001C
}; //Size=0x0020

class cstream_render_gfx
{
public:
	char m_pad_0x0000[0x48]; //0x0000
}; //Size=0x0048

class ccustom_shader_effects
{
public:
	char m_pad_0x0000[0xA4]; //0x0000
	ccolour m_primary_colour; //0x00A4 
	ccolour m_secondary_colour; //0x00A8 
}; //Size=0x00AC

class creplay_interface
{
public:
	char m_pad_0x0000[0x10]; //0x0000
	creplay_interface_vehicle* m_replay_interface_vehicle; //0x0010 
	creplay_interface_ped* m_replay_interface_ped; //0x0018 
	creplay_interface_pickup* m_replay_interface_pickup; //0x0020 
	creplay_interface_object* m_replay_interface_object; //0x0028 
}; //Size=0x0030

class cvehicle_handle
{
public:
	cvehicle* m_vehicle; //0x0000 
	__int32 m_handle;
	char _pad0[0x4];
}; //Size=0x0010

class cvehicle_list
{
public:
	cvehicle_handle vehicles[300]; //0x0000 
}; //Size=0x12C0


class creplay_interface_vehicle
{
public:
	char m_pad_0x0000[0x180]; //0x0000
	cvehicle_list* m_vehicle_list; //0x0180 
	int32_t m_max_vehicles; //0x0188 
	char m_pad_0x018C[0x4]; //0x018C
	int32_t m_current_vehicles; //0x0190 
	char m_pad_0x0194[0x4]; //0x0194

	cvehicle* get_vehicle(const int& index) const
	{
		if (index < m_max_vehicles)
			return m_vehicle_list->vehicles[index].m_vehicle;
		return nullptr;
	}
}; //Size=0x0198


class cped_handle
{
public:
	cped* m_ped; //0x0000 
	__int32 m_handle;
	char _pad0[0x4];
}; //Size=0x0010

class cped_list
{
public:
	cped_handle peds[256]; //0x0000 
}; //Size=0x1000


class creplay_interface_ped
{
public:
	char m_pad_0x0000[0x100]; //0x0000
	cped_list* m_ped_list; //0x0100 
	uint32_t m_max_peds; //0x0108 
	char m_pad_0x010C[0x4]; //0x010C
	uint32_t m_current_peds; //0x0110 
	char m_pad_0x0114[0x34]; //0x0114

	cped* get_ped(const uint32_t& index) const
	{
		if (index < m_max_peds)
			return m_ped_list->peds[index].m_ped;
		return nullptr;
	}
}; //Size=0x0118


class creplay_interface_pickup
{
public:
	char m_pad_0x0000[0x8]; //0x0000
}; //Size=0x0008

class creplay_interface_object
{
public:
	char m_pad_0x0000[0x8]; //0x0000
}; //Size=0x0008

class ccurrent_ped_cam
{
public:
	char m_pad_0x0000[0x10]; //0x0000
	ccamera_meta_data* m_camera_meta_data; //0x0010 
	char m_pad_0x0018[0x28]; //0x0018
	v3 m_viewing_angles; //0x0040 
	char m_pad_0x004C[0x14]; //0x004C
	v3 m_crosshair_location; //0x0060 
}; //Size=0x006C

class ccamera_meta_data
{
public:
	char m_pad_0x0000[0x30]; //0x0000
	float m_camera_fov; //0x0030 
}; //Size=0x0034

class ccam_interface
{
public:
	ccam_gameplay_director* m_gam_gameplay_director; //0x0000 
	char m_pad_0x0008[0x38]; //0x0008
}; //Size=0x0040

class ccam_gameplay_director
{
public:
	char m_pad_0x0000[0x2C0]; //0x0000
	ccurrent_ped_cam* m_current_ped_cam; //0x02C0 
}; //Size=0x02C8

class cattacker
{
public:
	cped* CPed0; //0x0000
	char pad_0x0008[0x10]; //0x0008
	cped* CPed1; //0x0018
	char pad_0x0020[0x10]; //0x0020
	cped* CPed2; //0x0030
}; //Size=0x0038

class cwater_data
{
public:
	__int16 iMinX; //0x0000 X Coord 1
	__int16 iMinY; //0x0002  Y Coord 1
	__int16 iMaxX; //0x0004 X Coord 2
	__int16 iMaxY; //0x0006 Y Coord 2
	__int8 iAlphaSW; //0x0008  (South West, default 26)
	__int8 iAlphaSE; //0x0009  (South East, default 26)
	__int8 iAlphaNW; //0x000A  (North West, default 26)
	__int8 iAlphaNE; //0x000B  (North East, default 26)
	char _0x000C[8]; // (Unknown, appear to be two floats?)
	float fHeight; //0x0014 (Z-Height, default 0.0)
	BYTE bHasLimitedDepth; //0x0018  (Second bit [binary 10] = On, gives the water quad an effective range of 6 z-points)
	char _0x0019[3]; // (Unknown)
}; //Size=0x001C


class cwater_quads
{
public:
	char m_pad_0x0000[0x8]; //0x0000
	cwater_data m_water_quads[821]; //0x0008 
}; //Size=0x59D4


class cmodel_info
{
public:
	char m_pad_0x0000[0x18]; //0x0000
	uint32_t m_model_hash; //0x0018 
	char m_pad_0x001C[0x14]; //0x001C
	float m_min_dimension_x; //0x0030 
	float m_min_dimension_y; //0x0034 
	float m_min_dimension_z; //0x0038 
	char m_pad_0x003C[0x4]; //0x003C
	float m_max_dimension_x; //0x0040 
	float m_max_dimension_y; //0x0044 
	float m_max_dimension_z; //0x0048 
	char m_pad_0x004C[0x17C]; //0x004C
	char* m_ped_display_name; //0x01C8 
	char m_pad_0x01D0[0xC8]; //0x01D0
	char m_vehicle_display_name[0x8]; //0x0298 
	char m_pad_0x02A0[0x2A8]; //0x02A0
	uint8_t m_model_class; //0x0548 
	char m_pad_0x0549[0x7]; //0x0549
};

class centity_vtable
{
public:
	char m_pad_0x0000[0x1D8]; //0x0000
	char(*set_entity_coords)(int64_t a1, int64_t a2, int a3, char a4, char a5, char a6, char a7, char a8, char a9);
	//0x01D8 
	char m_pad_0x01E0[0x188]; //0x01E0
	v3* (*get_velocity)(centity* entity); //0x0368 
}; //Size=0x0370

class cped_factory_vtable
{
public:
	char m_pad_0x0000[0x48]; //0x0000
}; //Size=0x0048

class cnet_object_entity
{
public:
	char m_pad_0x0000[0x49]; //0x0000
	uint8_t m_player_id; //0x0049 
	char m_pad_0x004A[0x6]; //0x004A
}; //Size=0x0050

class ccdimage
{
public:
	cmodels* Models; //0x0000 
	WORD m_maximum_models; //0x0008 
	char m_pad_0x000A[0x36]; //0x000A
}; //Size=0x0040

class cmodels
{
public:
	char m_pad_0x0000[0x8]; //0x0000
	uint8_t m_start; //0x0008 
	char m_pad_0x0009[0x7]; //0x0009
}; //Size=0x0010

class cmodel
{
public:
	uint32_t m_model_hash; //0x0000 
	char m_pad_0x0004[0x4]; //0x0004
}; //Size=0x0008

class cviewport
{
public:
	char _0x0000[0x24C];
	float fViewMatrix[0x10];
}; //Size=0x028C

class cblip
{
public:
	__int32 iID; //0x0000
	__int8 iID2; //0x0004
	char _0x0005[3];
	BYTE N000010FB; //0x0008 (80 = moves with player, some values will turn icon into map cursor and break it)
	char _0x0009[7];
	v3 v3Pos;
	char _0x001C[6];
	BYTE btFocused; //0x0022   (Focused? 0100 0000)
	char _0x0023[5];
	char* szMessage; //0x0028 If not null, contains the string of whatever the blip says when selected.
	char _0x0030[16];
	int iIcon; //0x0040
	char _0x0044[4];
	DWORD dwColor; //0x0048 (Sometimes works?)
	char _0x004C[4];
	float fScale; //0x0050
	__int16 iRotation; //0x0054 Heading
	BYTE btInfoIDType; //0x0056 GET_BLIP_INFO_ID_TYPE
	BYTE btZIndex; //0x0057
	BYTE btDisplay; //0x0058  Also Visibility 0010
	BYTE btAlpha; //0x0059
}; //Size=0x005A

class cbliplist
{
public:
	cblip* m_Blips[0x400]; //0x0000
}; //Size=0x2F18

class cwaypoint
{
public:
	char m_pad_0x0000[0x20]; //0x0000
	float x; //0x0020 
	float y; //0x0024 
	char m_pad_0x0028[0x4]; //0x0028
}; //Size=0x002C

class cgta_time
{
public:
	char m_pad_0x0000[0x10]; //0x0000
	int8_t m_hour; //0x0010 
	int8_t m_minute; //0x0011 
}; //Size=0x0012

class cgame_version
{
public:
	char m_version[8]; //0x920B89C0 
}; //Size=0x0008


#pragma pack(pop)
#endif