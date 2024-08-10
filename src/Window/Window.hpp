#pragma once
#include "../Includes.hpp"

class Window
{
public:
	bool Transparent = true;
	bool Showing = true;

	void Create( std::function<void( )> callback );
};

inline Window window;