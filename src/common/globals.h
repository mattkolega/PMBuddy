#pragma once

#include "types.h"

#ifdef PMBUDDY_DEBUG
inline constexpr bool DEBUG_MODE = true;
#else
inline constexpr bool DEBUG_MODE = false;
#endif

inline constexpr u64 KILOBYTE = 1024;
inline constexpr u64 MEGABYTE = KILOBYTE * 1024;
inline constexpr u64 GIGABYTE = MEGABYTE * 1024;
