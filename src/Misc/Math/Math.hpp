#pragma once

#include <xmmintrin.h>
#include <emmintrin.h>
#include <cmath>

#include <json.hpp>

class Vector2
{
public:
	float x = 0.f, y = 0.f;
public:
	Vector2( ) {  }
	Vector2( float x, float y )
	{
		this->x = x;
		this->y = y;
	}

	Vector2( int x, int y )
	{
		this->x = x;
		this->y = y;
	}

	Vector2( ImVec2 pos )
	{
		this->x = pos.x;
		this->y = pos.y;
	}

	operator ImVec2( )
	{
		return ImVec2( this->x, this->y );
	}

	NLOHMANN_DEFINE_TYPE_INTRUSIVE( Vector2, x, y )
};

class Vector3
{
public:
	float x, y, z = 0.f;
public:
	Vector3( )
	{
		x = y = z = 0.f;
	}
	Vector3( float x, float y, float z )
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float length( )
	{
		return sqrt( x * x + y * y + z * z );
	}

	float distance_to( const Vector3 v )
	{
		return Vector3( this->x - v.x, this->y - v.y, this->z - v.z ).length( );
	}

	float dot( Vector3 dot )
	{
		return (x * dot.x + y * dot.y + z * dot.z);
	}

	bool operator==( const Vector3 other )
	{
		return (x == other.x && y == other.y && z == other.z);
	}
};

class Vector4
{
public:
	float x, y, z, w;
public:
	Vector4( )
	{
		x = y = z = w = 0;
	}
	Vector4( float x, float y, float z, float w )
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
};