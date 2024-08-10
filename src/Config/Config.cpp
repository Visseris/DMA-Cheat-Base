#include "Config.hpp"

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

bool Config::Load( const std::string name )
{
	const std::string file = name + _( ".conf.json" );
	std::ifstream ifs( file );
	if ( !ifs || !ifs.is_open( ) )
		return false;

	try
	{
		json JsonCfg = nlohmann::json::parse( ifs );
		cfg = JsonCfg;
	} 
	catch ( json::exception& e )
	{
		return false;
	}

	ifs.close( );

	return true;
}

bool Config::Save( const std::string name )
{
	json JsonFile = cfg;

	const std::string file = name + _( ".conf.json" );
	std::ofstream ofs( file );
	if ( !ofs || !ofs.is_open( ) )
		return false;

	const std::string dump = JsonFile.dump( );

	ofs.write( dump.c_str( ), dump.size( ) );

	if ( ofs.fail( ) )
		return false;

	ofs.close( );

	return true;
}

bool Config::Delete( const std::string name )
{
	const std::string file = name + _( ".conf.json" );
	if ( !fs::exists( file ) )
		return false;

	return fs::remove( file );
}

std::vector<std::string> Config::GetAvailable( )
{
	std::vector<std::string> configFiles;
	fs::path currentDir = fs::current_path( );

	for ( const auto& entry : fs::directory_iterator( currentDir ) )
	{
		if ( !entry.is_regular_file( ) || entry.path( ).extension( ) != _( ".json" ) )
			continue;

		auto filename = entry.path( ).filename( ).string( );
		if ( filename.ends_with( _( ".conf.json" ) ) )
		{
			filename = filename.substr( 0, filename.find_first_of( '.' ) );
			configFiles.push_back( filename );
		}
	}

	return configFiles;
}