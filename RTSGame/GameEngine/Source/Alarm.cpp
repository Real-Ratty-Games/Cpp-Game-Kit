/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Public/Alarm.hpp"

using namespace GameEngine;

/// <summary>
/// Insert new alarm module
/// </summary>
/// <param name="name">module name</param>
/// <param name="method">method</param>
/// <param name="count">start count</param>
void Alarm::PushModule(strgv name, std::function<int64()> method, int64 count)
{
	strg sname(name);
	if (!mModules.contains(sname))
	{
		AlarmModule result;
		result.Method = method;
		result.Count = count;
		mModules.insert(std::make_pair(sname, result));

		if (count > GAMEENGINE_ALARM_DISABLE && !mActiveModules.contains(sname))
			mActiveModules.insert(sname);
	}
}

/// <summary>
/// Set count of existing module
/// </summary>
/// <param name="name">module name</param>
/// <param name="count"></param>
void Alarm::SetModuleCount(strgv name, int64 count)
{
	strg sname(name);
	if (mModules.contains(sname))
	{
		mModules[sname].Count = count;

		if (count > GAMEENGINE_ALARM_DISABLE && !mActiveModules.contains(sname))
			mActiveModules.insert(sname);
		else if(count <= GAMEENGINE_ALARM_DISABLE)
			mActiveModules.erase(sname);
	}
}

/// <summary>
/// Set true if active module should be paused
/// </summary>
/// <param name="name">module name</param>
/// <param name="paused">true if paused</param>
void Alarm::SetModulePaused(strgv name, bool paused)
{
	strg sname(name);
	if (mModules.contains(sname))
		mModules[sname].bPaused = paused;
}

/// <summary>
/// Returns true if module is active and not paused
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
bool Alarm::IsModuleActive(strgv name)
{
	strg sname(name);
	if (mModules.contains(sname))
		return mActiveModules.contains(sname) && !mModules[sname].bPaused;
	return false;
}

/// <summary>
/// Advance module counters and execute methods
/// </summary>
void Alarm::Tick()
{
	std::vector<strg> toRemove;
	toRemove.reserve(mActiveModules.size());

	for (auto& it : mActiveModules)
	{
		auto& module = mModules[it];
		if (module.bPaused) continue;

		module.Count--;
		if (module.Count <= GAMEENGINE_ALARM_DISABLE)
		{
			module.Count = module.Method();

			if (module.Count <= GAMEENGINE_ALARM_DISABLE)
				toRemove.push_back(it);
		}
	}

	if (!toRemove.empty())
	{
		for (auto& it : toRemove)
			mActiveModules.erase(it);
	}
}
