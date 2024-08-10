#pragma once
#include "../../Includes.hpp"

class OffsetsReader
{
private:
	std::string file;
public:
	OffsetsReader( const std::string file )
	{
		this->file = file;
	}

	bool Read( );
};