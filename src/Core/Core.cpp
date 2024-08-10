#include "Core.hpp"

void Core::Run( )
{
	while ( !G::Exit )
	{
		std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

		DWORD ProcessId = mem.GetPidFromName( _( PROCESS_NAME ) );
		if ( ProcessId != G::ProcessId )
		{
			G::Exit = true;
			continue;
		}
	}
}