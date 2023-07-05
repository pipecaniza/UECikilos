#pragma once

struct V3
{
	real32 X;
	real32 Y;
	real32 Z;
};

struct V2
{
	real32 X;
	real32 Y;
};

function V3
MakeV3(real32 X, real32 Y, real32 Z)
{
	V3 Result = { X, Y, Z };
	return Result;
}

function V2
MakeV2(real32 X, real32 Y)
{
	V2 Result = { X, Y };
	return Result;
}