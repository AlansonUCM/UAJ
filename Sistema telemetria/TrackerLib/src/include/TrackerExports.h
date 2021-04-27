#pragma once

#ifdef	TRACKER_CORE_EXPORTS
#define TRACKER_CORE_API __declspec(dllexport)
#else
#define TRACKER_CORE_API __declspec(dllimport)
#endif