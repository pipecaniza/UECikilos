#pragma once

#ifndef NO_INCLUDE
#include "eq_globals.h"
#endif


struct memory_arena
{
	memory_index Size;
	uint8* Base;
	memory_index Used;
};

function void
InitializeArena(memory_arena* Arena, memory_index Size, uint8* Base)
{
	Arena->Size = Size;
	Arena->Base = Base;
	Arena->Used = 0;
}

#define PushStruct(Arena, Type) (Type *) PushSize_(Arena, sizeof(Type))
#define PushArray(Arena, Count, Type) (Type *) PushSize_(Arena, sizeof(Type) * Count)
inline void*
PushSize_(memory_arena* Arena, memory_index Size)
{
	// Assert
	uint8* Base = Arena->Base + Arena->Used;
	Arena->Used += Size;
	return Base;
}