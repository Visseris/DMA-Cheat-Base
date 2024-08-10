#pragma once
#include <unordered_map>
#include "../Misc/Security/Safe.hpp"

#define OFFSET(name, value) inline uint32_t name = value; \
	namespace detail { \
		struct Register##name { \
			Register##name() { OffsetMap[_( #name )] = &name; } \
		}; \
		inline Register##name register_##name; \
	}

namespace Offsets
{
	inline std::unordered_map<std::string, uint32_t*> OffsetMap{ };

	// Example Offset
	OFFSET health( 0x1234 );
}