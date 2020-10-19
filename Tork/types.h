#pragma once
#ifndef TYPES_H
#define TYPES_H

enum ConsoleColours : uint8_t
{
	GREEN = 10,
	CYAN,
	RED,
	PURPLE,
	YELLOW,
	WHITE,
};

struct fiveBytes
{
	BYTE byte[5];
};

struct MemoryPool
{
	uintptr_t list_addr;
	char* bool_adr;
	int max_count;
	int item_size;
};


enum InitlisationErrors : uint8_t
{
	SUCCESS,
	HOOK_ERROR,
	PATTERN_ERROR,
	KEYBOARD_ERROR,
	STATE_ERROR
};

enum Controls
{
	WEAPON_WHEEL = 37,
	TAKE_COVER = 44,
	DIVE = 55,
	ControlPhone = 27,
	ControlMeleeAttackLight = 140,
	ControlCharacterWheel = 19,
	ControlVehicleHeadlight = 74,
	ControlVehicleRadioWheel = 85,
	ControlVehicleNextRadio = 81,
	ControlVehiclePrevRadio = 82,
	ControlVehicleNextRadioTrack = 83,
	ControlVehiclePrevRadioTrack = 84,
	ControlCinematicSlowMo = 7,
	ControlVehicleFlyAttackCamera = 121,
	ControlVehicleCinCam = 80,
	ControlMap = 156,
	ControlHUDSpecial = 48,
	PHONE_UP = 172,
	PHONE_DOWN = 173,
	PHONE_LEFT = 174,
	PHONE_RIGHT = 175,
	PHONE_SELECT = 176,
	PHONE_CANCEL = 177,
	ControlFrontendDown = 187,
	ControlFrontendUp = 188,
	ControlFrontendLeft = 189,
	ControlFrontendRight = 190,
	ControlScriptPadUp = 232,
	ControlScriptPadDown = 233,
	ControlScriptPadLeft = 234,
	ControlScriptPadRight = 235,
	VEHICLE_BRAKE = 72,
	VEHICLE_HANDBRAKE = 76,
	VEHICLE_HORN = 86,
	ControlAim = 25,
};

struct Screen
{
	uint32_t w, h;
};

enum ClearConsole : bool
{
	CLEAR = true,
	DONT_CLEAR = false
};

enum ClosableConsole : bool
{
	CLOSABLE = true,
	UNCLOSABLE = false
};

enum TickFunction : bool
{
	ON_TICK = true,
	ON_DELAY = false
};

class ccolour
{
public:
	BYTE r, g, b, a;

	ccolour& swap_r_b()
	{
		std::swap(r, b);
		return *this;
	}
};

class TextInfo
{
public:
	ccolour color;
	float   f_text_scale1;
	float   f_text_scale2;
	float   f_text_wrap_start;
	float   f_text_wrap_end;
	BYTE    i_font;
	WORD    w_not_centered;
	BYTE    bt_drop_shadow;
	BYTE    bt_text_outline;
	BYTE    unk1;
	BYTE    unk2;
	BYTE    unk3;
	BYTE    unk4;

	void set_color(ccolour c)
	{
		c.swap_r_b();
		color = c;
	}

	void set_scale(const float f)
	{
		f_text_scale1 = f;
		f_text_scale2 = f;
	}
};

typedef union
{
	uint32_t m_raw;

	struct
	{
		uint8_t m_ip_4;
		uint8_t m_ip_3;
		uint8_t m_ip_2;
		uint8_t m_ip_1;
	}m_split;
}ip_address;

typedef union
{
	uint32_t m_raw;

	struct
	{
		uint8_t m_proof_1;
		uint8_t m_invincible;
		uint8_t m_proof_3;
		uint8_t m_proof_4;
	}m_split;
}entity_proofs;

#pragma pack(push, 1)
typedef struct
{
	float x;
	DWORD _paddingx;
	float y;
	DWORD _paddingy;
	float z;
	DWORD _paddingz;
}vector3;
#pragma pack(pop)

#define CBLACK 0,0,0,220
#define CFULLBLACK 0,0,0,255
#define CWHITE 255,255,255,255
#define CGREY 21,21,21,210
#define CGREY2 42,42,42,140
#define CBLUE 96,157,255,165
#define CLIGHTGREY 66,135,245,255 //238,6,6,165 // 32,32,32,255 //
#define CWHITE2 120,120,120,255
#define CGREEN 0,255,0,255
#define CRED1 230,25,25,255

#define MAX_KEYS (0x100)
#define SNOW_BIT_ARRAY_GET_REQUIRED_BYTES(bits)        (((bits + 8 -1) / 8))
#define SNOW_BIT_ARRAY_GET_RELATIVE_BYTE_INDEX(bit)    ((bit / 8))
#define SNOW_BIT_ARRAY_GET_RELATIVE_BIT_INDEX(bit)    ((bit % 8))

enum
{
	KEY_STATE_PRESSED,
	KEY_STATE_HELD_DOWN,
	KEY_STATE_FIRST_PRESS,
};


#define MENU_OPEN VK_INSERT
#define MENU_UP VK_NUMPAD8
#define MENU_DOWN VK_NUMPAD2
#define MENU_BACK VK_NUMPAD0
#define MENU_LEFT VK_NUMPAD4
#define MENU_RIGHT VK_NUMPAD6
#define MENU_SELECT VK_NUMPAD5

#endif