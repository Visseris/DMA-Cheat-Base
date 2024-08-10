#pragma once
#include "../../Includes.hpp"

#include <imgui/imgui.h>

namespace Renderer
{
	inline bool OnScreen( const ImVec2& pos )
	{
		return true;
	}

	inline void AddLine( const ImVec2& p1, const ImVec2& p2, ImU32 col, float thickness )
	{
		if ( !OnScreen( p1 ) || !OnScreen( p2 ) ) return;
		ImGui::GetBackgroundDrawList( )->AddLine( p1, p2, col, thickness );
	}

	inline void AddLineStroked( const ImVec2& p1, const ImVec2& p2, ImU32 col, float thickness )
	{
		float alpha = ImGui::ColorConvertU32ToFloat4( col ).w;

		AddLine( ImVec2( p1.x - thickness, p1.y - thickness ), ImVec2( p2.x - thickness, p2.y - thickness ), ImColor( 0.f, 0.f, 0.f, alpha ), thickness );
		AddLine( p1, p2, col, thickness );
	}

	inline void AddCircle( const ImVec2& center, float radius, ImU32 col, int num_segments = 0, float thickness = 1.f )
	{
		if ( !OnScreen( center ) ) return;
		ImGui::GetBackgroundDrawList( )->AddCircle( center, radius, col, num_segments, thickness );
	}

	inline void AddCircleFilled( const ImVec2& center, float radius, ImU32 col, int num_segments = 0 )
	{
		if ( !OnScreen( center ) ) return;
		ImGui::GetBackgroundDrawList( )->AddCircleFilled( center, radius, col, num_segments );
	}

	inline void AddText( const ImVec2& pos, ImU32 col, const char* text_begin, ImFont* font = nullptr, float font_size = -1.0f )
	{
		if ( !OnScreen( pos ) ) return;

		ImGui::GetBackgroundDrawList( )->AddText( font, font_size, pos, col, text_begin );
	}

	inline void AddTextStroked( const ImVec2& pos, ImU32 col, const char* text_begin, ImFont* font = nullptr, float font_size = -1.0f )
	{
		float alpha = ImGui::ColorConvertU32ToFloat4( col ).w;

		AddText( ImVec2( pos.x - 1.f, pos.y - 1.f ), col, text_begin, font, font_size );
		AddText( pos, col, text_begin, font, font_size );
	}
}