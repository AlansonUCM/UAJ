#pragma once

#ifdef	TRACKER_CORE_EXPORTS
//#define TRACKER_CORE_API __declspec(dllexport)
#define TRACKER_CORE_API
#else
//#define TRACKER_CORE_API __declspec(dllimport)
#define TRACKER_CORE_API
#endif