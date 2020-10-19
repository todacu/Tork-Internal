#include "pch.h"
#include "keyboard.h"
#include "types.h"
#include "input_hook.h"

const int keys_size = 255;

struct
{
	DWORD time;
	BOOL  is_with_alt;
	BOOL  was_down_before;
	BOOL  is_up_now;
}         key_states[keys_size];

void on_keyboard_message(const DWORD key, WORD repeats, BYTE scan_code, BOOL is_extended, const BOOL is_with_alt, const BOOL  was_down_before, const BOOL is_up_now)
{
	if (key < keys_size)
	{
		key_states[key].time = GetTickCount();
		key_states[key].is_with_alt = is_with_alt;
		key_states[key].was_down_before = was_down_before;
		key_states[key].is_up_now = is_up_now;
	}
}

const int now_period = 1000, max_down = 5000; // ms
bool key_down(const DWORD key, const bool exclusive)
{
	const auto b = key < keys_size ? GetTickCount() < key_states[key].time + now_period && key_states[key].is_up_now : false;
	if (b&& exclusive)
		reset_key_state(key);
	return b;
}


void reset_key_state(const DWORD key)
{
	if (key < keys_size)
		memset(&key_states[key], 0, sizeof key_states[0]);
}


bool get_key(const uint8_t key, const bool check_delay, const uint16_t activation_delay, const uint16_t hold_delay)
{
	const bool key_state = key_states_menu[key].get_bit(KEY_STATE_PRESSED);
	if (!check_delay)
		return key_state;
	if (key_states_menu[VK_SHIFT].get_bit(KEY_STATE_PRESSED))
		key_states_menu[key] = false;

	const bool first_press = key_states_menu[key].get_bit(KEY_STATE_FIRST_PRESS);

	const bool     held_down = key_states_menu[key].get_bit(KEY_STATE_HELD_DOWN);
	const uint16_t delay = held_down * hold_delay + !held_down * activation_delay;

	const uint32_t  tick_count = GetTickCount();
	static uint32_t past_tick_counts[MAX_KEYS] = { tick_count };

	bool result = false;
	if (key_state)
	{
		if (!first_press || tick_count - past_tick_counts[key] > delay)
		{
			if (first_press)
			{
				key_states_menu[key].set_bit(KEY_STATE_HELD_DOWN);
			}
			key_states_menu[key].set_bit(KEY_STATE_FIRST_PRESS);
			past_tick_counts[key] = tick_count;
			result = true;
		}
	}
	return result;
}