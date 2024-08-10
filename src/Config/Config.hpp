#pragma once
#include "../Includes.hpp"

#include <json.hpp>
using json = nlohmann::json;

namespace Config
{
	bool Load( const std::string name );
	bool Save( const std::string name );
	bool Delete( const std::string name );

	std::vector<std::string> GetAvailable( );
}

struct CheatConfig
{
	int MenuKey = VK_RMENU;
	int OverlayToggleKey = VK_SPACE;

	bool OverlayVsync = true;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE( CheatConfig, MenuKey, OverlayToggleKey, OverlayVsync );
};

inline CheatConfig cfg;