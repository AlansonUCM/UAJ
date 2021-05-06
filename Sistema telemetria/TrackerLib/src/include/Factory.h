#pragma once

#include <map>
#include "TrackerExports.h"
class ITrackerAsset;

template <typename T>
class TRACKER_CORE_API Factory
{
public:
	template <typename TChild>
	void registerType(std::string name) {
		static_assert(std::is_base_of<T, TChild>::value, "Factory::registerType doesn't accept this type because doesn't derive from base class");
		createFunctions[name] = &createFunction<TChild>;
	}


	T* create(std::string name) {
		auto it = createFunctions.find(name);
		if (it != createFunctions.end())
			return (*it).second();

		return nullptr;
	}

private:
	template <typename TChild>
	static T* createFunction()
	{
		return new TChild();
	}

	typedef T* (*PCreateFunc)();
	std::map<std::string, PCreateFunc> createFunctions;
};

