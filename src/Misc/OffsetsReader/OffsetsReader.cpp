#include "OffsetsReader.hpp"
#include "../../SDK/Offsets.hpp"

#include <fstream>
#include <sstream>

void UpdateOffset( const std::string key, uint32_t value )
{
	auto& map = Offsets::OffsetMap;

	auto it = map.find( key );
	if ( it == map.end( ) )
	{
		std::cerr << _( "Invalid key: " ) << key << std::endl;
		return;
	}

	*(it->second) = value;
}

bool OffsetsReader::Read( )
{
	std::ifstream ifs( this->file );
	if ( !ifs.is_open( ) ) return false;

	std::string line;
	while ( std::getline( ifs, line ) )
	{
		std::istringstream ss( line );
		std::string key;
		uint32_t value;

		if ( std::getline( ss, key, '=' ) )
		{
			ss >> std::hex >> value;
			UpdateOffset( key, value );
		}
	}

	return true;
}