#pragma once
#ifndef SPOTIFY_INT_H
#define SPOTIFY_INT_H

DWORD WINAPI checkSpotifySong();
void grabHwnd();
void pauseOrPlay();
void sendPlayKey();
extern bool isSongPlaying;
extern std::string nowPlaying;
extern std::string lastNowPlaying;

#endif