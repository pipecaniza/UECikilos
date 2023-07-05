#pragma once
#include <stdint.h>
#include <stddef.h>

#define local_variable static
#define global_variable static
#define function static
#define internal static

#define Kilobytes(Value) ((Value)*1024)
#define Megabytes(Value) (Kilobytes(Value)*1024)
#define Gigabytes(Value) (Megabytes(Value)*1024)

typedef int8_t int8;
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef int32_t int32;
typedef uint32_t uint32;
typedef int32_t bool32;
typedef size_t memory_index;
typedef float real32;

struct buffer
{
	uint8 *Data;
	uint32 Size;
};
typedef buffer string;

#define BundleStringC(S) MakeString((uint8*)S, strlen(S))
inline function string
MakeString(uint8 *Address, uint32 Size)
{
	string Result = {};
	Result.Data = Address;
	Result.Size = Size;
	return Result;
}