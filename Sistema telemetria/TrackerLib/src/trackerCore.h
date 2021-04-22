#pragma once

#ifdef	TRACKERCORE_EXPORTS
#define TRACKERCORE_API __declspec(dllexport)
#else
#define TRACKERCORE_API __declspec(dllimport)
#endif