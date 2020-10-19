// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.
#pragma once
#ifndef PCH_H
#define PCH_H

#define WIN32_LEAN_AND_MEAN
#pragma comment(lib,"minhook/lib/libMinHook-x64-v140-mdd.lib")

// Windows Header Files
#include <windows.h>
#include <cstdio>
#include <cstdint>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <regex>
#include <TlHelp32.h> 
#include <time.h>

#include "vector.h"

#endif //PCH_H