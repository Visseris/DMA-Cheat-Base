#include "Menu.hpp"
#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

#include "../Window.hpp"

bool Menu::IsOpen = true;

void Menu::Render( )
{
	if ( !Menu::IsOpen ) return;

	ImGui::Begin( _( "Menu" ) );
	{
		if ( ImGui::BeginTabBar( _( "##MainTabBar" ) ) )
		{
			if ( ImGui::BeginTabItem( _( "Settings" ) ) )
			{
				ImGui::Checkbox( _( "Transparent Window" ), &window.Transparent );
				ImGui::Checkbox( _( "Overlay V-Sync" ), &cfg.OverlayVsync );

				if ( ImGui::Button( _( "Exit" ) ) )
				{
					G::Exit = true;
				}

				ImGui::EndTabItem( );
			}

			if ( ImGui::BeginTabItem( _( "Configs" ) ) )
			{
				static int selectedConfig = -1;
				static auto configs = Config::GetAvailable( );

				auto content = ImGui::GetContentRegionAvail( ); content.y -= 30;

				ImGui::BeginChild( _( "##ConfigsList" ), content, ImGuiChildFlags_Border );
				{
					for ( int i = 0; i < configs.size( ); i++)
					{
						auto config = configs[ i ];
						bool selected = selectedConfig == i;

						if ( ImGui::Selectable( config.c_str( ), &selected ) )
							selectedConfig = selectedConfig == i ? -1 : i;

						ImGui::SetItemDefaultFocus( );
					}
				}
				ImGui::EndChild( );

				if ( selectedConfig != -1 )
				{
					if ( ImGui::Button( _( "Overwrite" ) ) )
					{
						Config::Save( configs[ selectedConfig ] );
					}

					ImGui::SameLine( );

					if ( ImGui::Button( _( "Load" ) ) )
					{
						Config::Load( configs[ selectedConfig ] );
					}

					ImGui::SameLine( );

					if ( ImGui::Button( _( "Delete" ) ) )
					{
						Config::Delete( configs[ selectedConfig ] );

						selectedConfig = -1;
						configs = Config::GetAvailable( );
					}
				}
				else
				{
					static std::string ConfigName = "";
					ImGui::InputTextWithHint( _( "##ConfigName" ), _( "Config Name" ), &ConfigName );
					
					ImGui::SameLine( );

					if ( ImGui::Button( _( "Save" ) ) )
					{
						Config::Save( ConfigName );
						ConfigName.clear( );

						configs = Config::GetAvailable( );
					}
				}

				ImGui::EndTabItem( );
			}

			ImGui::EndTabBar( );
		}
	}
	ImGui::End( );
}