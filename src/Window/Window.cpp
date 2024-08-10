#include "Window.hpp"
#include "dx.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>

#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

#define EX_STYLES WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT

using namespace dx;
HWND _hwnd;

bool showing = true;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
LRESULT __stdcall WndProc( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
    if ( ImGui_ImplWin32_WndProcHandler( hwnd, msg, wparam, lparam ) )
        return 0L;

    if ( msg == WM_QUIT || msg == WM_DESTROY )
    {
        G::Exit = true;
        return 0L;
    }

    if ( msg == WM_SIZE )
    {
        if ( g_pd3dDevice != NULL && wparam != SIZE_MINIMIZED )
        {
            clean_render_target( );
            g_pSwapChain->ResizeBuffers( 0, (UINT)LOWORD( lparam ), (UINT)HIWORD( lparam ), DXGI_FORMAT_UNKNOWN, 0 );
            create_render_target( );
        }
    }

    return DefWindowProcA( hwnd, msg, wparam, lparam );
}

void Window::Create( std::function<void( )> callback )
{
    HMODULE instance = SAFE_CALL( GetModuleHandleA )(0);
    WNDCLASSEX wc = { sizeof( wc ), CS_CLASSDC, (WNDPROC)WndProc, 0L, 0L, instance, NULL, NULL, NULL, NULL, _( "Cheat Window" ), NULL };

    SAFE_CALL( RegisterClassExA )(&wc);

    int x = SAFE_CALL( GetSystemMetrics )(SM_CXSCREEN);
    int y = SAFE_CALL( GetSystemMetrics )(SM_CYSCREEN);

    G::ScreenRes = Vector2( x, y );

    _hwnd = CreateWindowExA( EX_STYLES, wc.lpszClassName, wc.lpszClassName, WS_POPUP, 0, 0, x, y, 0, 0, wc.hInstance, 0 );

    if ( !create_device_d3d( _hwnd ) )
    {
        clean_device( );
        return;
    }

    MARGINS margins{ 0, 0, x, y };
    DwmExtendFrameIntoClientArea( _hwnd, &margins );

    SAFE_CALL( ShowWindow )(_hwnd, SW_SHOW);
    SAFE_CALL( UpdateWindow )(_hwnd);

    IMGUI_CHECKVERSION( );

    ImGui::CreateContext( );
    ImGuiIO& io = ImGui::GetIO( );

    io.LogFilename = nullptr;
    io.IniFilename = nullptr;

    io.Fonts->AddFontFromFileTTF( _( "C:\\Windows\\Fonts\\Tahoma.ttf" ), 16.f );
    io.Fonts->AddFontDefault( );

    ImGui::StyleColorsDark( );

    // Initialize ImGui Backends
    ImGui_ImplWin32_Init( _hwnd );
    ImGui_ImplDX11_Init( g_pd3dDevice, g_pd3dDeviceContext );

    MSG msg;
    ZeroMemory( &msg, sizeof( msg ) );

    while ( !G::Exit )
    {
        if ( ::PeekMessageA( &msg, NULL, 0U, 0U, PM_REMOVE ) )
        {
            if ( msg.message == WM_QUIT )
                break;

            ::TranslateMessage( &msg );
            ::DispatchMessageA( &msg );
            continue;
        }

        if ( !this->Showing && showing ) {
            SAFE_CALL( ShowWindow )( _hwnd, SW_HIDE );
            showing = false;
        }

        if ( this->Showing && !showing ) {
            SAFE_CALL( ShowWindow )( _hwnd, SW_SHOW );
            showing = true;
        }

        ImGui_ImplDX11_NewFrame( );
        ImGui_ImplWin32_NewFrame( );
        ImGui::NewFrame( );

        if ( !this->Transparent )
        {
            ImGui::GetBackgroundDrawList( )->AddRectFilled( ImVec2( 0, 0 ), ImVec2( x, y ), ImColor( 0, 0, 0, 255 ) );
        }
        
        callback( );

        ImGui::EndFrame( );

        ImGui::Render( );

        const float color[ 4 ] = { 0, 0, 0, 0 };
        g_pd3dDeviceContext->OMSetRenderTargets( 1, &g_mainRenderTargetView, nullptr );
        g_pd3dDeviceContext->ClearRenderTargetView( g_mainRenderTargetView, color );
        ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData( ) );

        g_pSwapChain->Present( cfg.OverlayVsync ? 1 : 0, 0 );
    }

    ImGui_ImplDX11_Shutdown( );
    ImGui_ImplWin32_Shutdown( );
    ImGui::DestroyContext( );

    clean_device( );

    SAFE_CALL( DestroyWindow )(_hwnd);
    SAFE_CALL( UnregisterClassA )(wc.lpszClassName, wc.hInstance);
}