#include "pch.h"
#include "spotify_int.h"
#include "dllmain.h"
#include "input.h"
#include "signatures.h"
#include "features.h"
#include "menu.h"

bool isSpotify(const PROCESSENTRY32W& entry)
{
	return std::wstring(entry.szExeFile) == L"Spotify.exe";
}

std::string nowPlaying;
std::string lastNowPlaying;
HWND spotifyHwnd;
BOOL CALLBACK enumWindowsProc(const HWND hwnd, const LPARAM lParam) {
	const std::vector<DWORD>& pids = *reinterpret_cast<std::vector<DWORD>*>(lParam);

	DWORD winId;
	GetWindowThreadProcessId(hwnd, &winId);

	for (DWORD pid : pids)
	{
		if (winId != pid)
			continue;
		std::wstring title(GetWindowTextLength(hwnd) + 1, L'\0');
		GetWindowTextW(hwnd, &title[0], title.size());

		if (std::regex_match(title.begin(), title.end(), std::regex(".*-.*")))
		{
			spotifyHwnd = hwnd;
			break;
		}
	}
	return TRUE;
}

void grabHwnd()
{
	std::vector<DWORD> pids;
	const HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32W entry;
	entry.dwSize = sizeof entry;

	if (!Process32FirstW(snap, &entry))
		return;

	do {
		if (isSpotify(entry)) {
			pids.emplace_back(entry.th32ProcessID);
		}
	} while (Process32NextW(snap, &entry));

	EnumWindows(enumWindowsProc, reinterpret_cast<LPARAM>(&pids));
}

void sendPlayKey()
{
	keybd_event(VK_MEDIA_PLAY_PAUSE, 0x12, NULL, NULL);
	Sleep(20);
	keybd_event(VK_MEDIA_PLAY_PAUSE, 0x12, KEYEVENTF_KEYUP, NULL);
}

bool isSongPlaying = false;
void pauseOrPlay()
{
	if (audio::get_player_radio_station_index() == 255 && !isSongPlaying)
	{
		sendPlayKey();
		isSongPlaying = true;
	}
	else if (audio::get_player_radio_station_index() != 255 && isSongPlaying)
	{
		sendPlayKey();
		isSongPlaying = false;
	}
	Sleep(100);
}

void updatePlaying()
{
	std::wstring title(GetWindowTextLength(spotifyHwnd) + 1, L'\0');
	GetWindowTextW(spotifyHwnd, &title[0], title.size());
	if (std::regex_match(title.begin(), title.end(), std::regex(".*-.*")))
		nowPlaying = std::string(title.begin(), title.end());

	if (nowPlaying == lastNowPlaying)
		return;

	isSongPlaying = !nowPlaying.empty();
	if (!nowPlaying.empty())
	{
		lastNowPlaying = nowPlaying;
	}
}

ULONGLONG lastSpotifyCheckTmr = GetTickCount64();
DWORD WINAPI checkSpotifySong()
{
	while (!initialisation::injected)
		Sleep(25);

	grabHwnd();
	while (!uninjecting)
	{
		if (GetTickCount64() > lastSpotifyCheckTmr + 100)
		{
			try
			{
				if ((myPed->inVehicle() || Features::Player::selfRadio) && Features::Spotify::spotifyRadioIntegration)
				{
					updatePlaying();
					pauseOrPlay();
				}
				lastSpotifyCheckTmr = GetTickCount64();
			}
			catch (...)
			{
				console::consoleLog("SPOTIFY UNKNOWN EXCEPTION", "Memory Exception!");
			}
		}
	}
	return 0;
}