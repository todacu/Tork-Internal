#pragma once
#ifndef KEYBOARD_H
#define KEYBOARD_H

void on_keyboard_message(DWORD key, WORD repeats, BYTE scan_code, BOOL is_extended, BOOL is_with_alt, BOOL  was_down_before, BOOL is_up_now);
bool key_down(DWORD key, bool exclusive = true);
void reset_key_state(DWORD key);
bool get_key(uint8_t key, bool check_delay, uint16_t activation_delay, uint16_t hold_delay);

#endif