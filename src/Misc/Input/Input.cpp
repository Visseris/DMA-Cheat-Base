#include "Input.hpp"

std::unordered_map<uint32_t, bool> prevKeyState;

bool Input::KeyDown( uint32_t key, bool remote )
{
	bool pressed = SAFE_CALL( GetAsyncKeyState )( key );
	if ( !pressed && remote )
		pressed = mem.GetKeyboard( )->IsKeyDown( key );

	return pressed;
}

bool Input::KeyPress( uint32_t key, bool remote )
{
	bool currentState = Input::KeyDown( key, remote );
	bool wasPressed = currentState && !prevKeyState[ key ];
	prevKeyState[ key ] = currentState;
	return wasPressed;
}