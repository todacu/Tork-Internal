#pragma once
#ifndef INPUT_HOOK_H
#define INPUT_HOOK_H

class InputHook
{
public:
	static InitlisationErrors initialize(const HWND h_window);
	static void remove();
	typedef void (*t_keyboard_fn)(DWORD key, WORD repeats, BYTE scan_code, BOOL is_extended, BOOL is_with_alt, BOOL was_down_before, BOOL is_up_now);
	static void keyboard_handler_register(t_keyboard_fn   function);
	static void keyboard_handler_unregister(t_keyboard_fn function);
};

template <size_t bits> class csnow_array_bit
{
private:
	uint8_t m_array[SNOW_BIT_ARRAY_GET_REQUIRED_BYTES(bits)] = { 0 };

public:
	csnow_array_bit();
	csnow_array_bit(bool bit_default_value);

	bool get_bit(size_t    absolute_bit_index);
	void set_bit(size_t    absolute_bit_index);
	void unset_bit(size_t  absolute_bit_index);
	void toggle_bit(size_t absolute_bit_index);

	size_t        get_array_byte_size() const;
	static size_t get_array_bit_count();
};

template <size_t bits> csnow_array_bit<bits>::csnow_array_bit()
{
	const size_t      bytes = sizeof(m_array);
	for (size_t index = 0; index < bytes; index++)
	{
		m_array[index] = 0;
	}
	return;
}

template <size_t bits> csnow_array_bit<bits>::csnow_array_bit(bool bit_default_value)
{
	const size_t      bytes = sizeof(m_array);
	const uint8_t     new_byte = bit_default_value * 0xFF;
	for (size_t index = 0; index < bytes; index++)
	{
		m_array[index] = new_byte;
	}
}

template <size_t bits> bool csnow_array_bit<bits>::get_bit(size_t absolute_bit_index)
{
	if (absolute_bit_index >= bits)
		return false;
	const size_t  relative_byte_index = SNOW_BIT_ARRAY_GET_RELATIVE_BYTE_INDEX(absolute_bit_index);
	const uint8_t relative_bit_index = SNOW_BIT_ARRAY_GET_RELATIVE_BIT_INDEX(absolute_bit_index);
	return (bool)((m_array[relative_byte_index] >> relative_bit_index) & 1);
}

template <size_t bits> void csnow_array_bit<bits>::set_bit(size_t absolute_bit_index)
{
	if (absolute_bit_index >= bits)
		return;
	const size_t  relative_byte_index = SNOW_BIT_ARRAY_GET_RELATIVE_BYTE_INDEX(absolute_bit_index);
	const uint8_t relative_bit_index = SNOW_BIT_ARRAY_GET_RELATIVE_BIT_INDEX(absolute_bit_index);
	m_array[relative_byte_index] |= 1 << relative_bit_index;
}


template <size_t bits> void csnow_array_bit<bits>::unset_bit(size_t absolute_bit_index)
{
	if (absolute_bit_index >= bits)
		return;
	const size_t  relative_byte_index = SNOW_BIT_ARRAY_GET_RELATIVE_BYTE_INDEX(absolute_bit_index);
	const uint8_t relative_bit_index = SNOW_BIT_ARRAY_GET_RELATIVE_BIT_INDEX(absolute_bit_index);
	m_array[relative_byte_index] &= ~(1 << relative_bit_index);
}

template <size_t bits> void csnow_array_bit<bits>::toggle_bit(size_t absolute_bit_index)
{
	if (absolute_bit_index >= bits)
		return;
	const size_t  relative_byte_index = SNOW_BIT_ARRAY_GET_RELATIVE_BYTE_INDEX(absolute_bit_index);
	const uint8_t relative_bit_index = SNOW_BIT_ARRAY_GET_RELATIVE_BIT_INDEX(absolute_bit_index);
	m_array[relative_byte_index] ^= 1 << relative_bit_index;
}

template <size_t bits> size_t csnow_array_bit<bits>::get_array_byte_size() const
{
	return sizeof(m_array);
}

template <size_t bits> size_t csnow_array_bit<bits>::get_array_bit_count()
{
	return bits;
}


extern csnow_array_bit<8> key_states_menu[MAX_KEYS];
static LRESULT APIENTRY window_process(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
#endif
