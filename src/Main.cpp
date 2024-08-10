#include <imgui/imgui.h>

#include "Includes.hpp"

#include "Window/Window.hpp"
#include "Window/Menu/Menu.hpp"

#include "Misc/OffsetsReader/OffsetsReader.hpp"
#include "Core/Core.hpp"

//#define OVERLAY_MODE

int main( )
{
#ifndef OVERLAY_MODE
	OffsetsReader reader( _( "offsets.txt" ) );
	if ( !reader.Read( ) )
	{
		printf( _( "Failed to read offsets from offsets.txt, proceeding with default.\n" ) );
	}

	SAFE_CALL( MessageBoxA )(0, _( "Press OK when the game is open" ), _( "DMA Cheat" ), MB_ICONINFORMATION);

	if ( !mem.Init( _( PROCESS_NAME ), false, false ) )
	{
		system( _( "pause" ) );
		return EXIT_FAILURE;
	}

	const auto information = mem.GetCurrentProcessInformation( );
	G::BaseAddr = information.base_address;
	G::BaseSize = information.base_size;
	G::ProcessId = information.PID;
	
	const auto procInfo = mem.GetProcessInformation( );
	G::PebAddr = procInfo.win.vaPEB;

	printf( _( "[+] PEB ADDR: 0x%llx\n" ), G::PebAddr );

	if ( !mem.GetKeyboard( )->InitKeyboard( ) )
	{
		system( _( "pause" ) );
		return EXIT_FAILURE;
	}
#endif

	printf( _( "Creating threads...\n" ) );

	auto CreateThreads = [&]( )
	{
		SAFE_CALL( CreateThread )(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(Core::Run), NULL, NULL, NULL);
		printf( _( "[+] Threads created!\n" ) );
	};

	CreateThreads( );

	window.Create( [&]( ) {
		if ( Input::KeyPress( cfg.OverlayToggleKey, false ) )
		{
			window.Showing ^= 1;
		}

		if ( !window.Showing ) return;

		if ( Input::KeyPress( cfg.MenuKey, true ) )
		{
			Menu::IsOpen ^= 1;
		}

		const std::string Watermark = _( "DMA Cheat | " ) + std::to_string( static_cast<int>(ImGui::GetIO( ).Framerate) ) + _( " FPS" );

		ImGui::GetBackgroundDrawList( )->AddText( ImVec2( 15, 15 ), IM_COL32_WHITE, Watermark.c_str( ) );
		
		Menu::Render( );
	} );

	std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

#ifndef OVERLAY_MODE
	VMMDLL_Close( mem.vHandle );
#endif

	return EXIT_SUCCESS;
}   