#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG //release build
	return "assets/";
#else
	return "P:/Projects/StarFighter/StarFighterGame/assets/";
#endif
}
