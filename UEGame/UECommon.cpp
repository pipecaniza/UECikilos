#include "UECommon.h"
#include "SpaceInvaders/Game/eq_globals.h"
#include "SpaceInvaders/Game/eq_common.h"

FVector V3ToFVector(V3* From)
{
	return FVector(From->X, From->Y, From->Z);
}

// TODO(pipecaniza): Should we use double instead real32 as UE?
V3 FVectorToV3(FVector* From)
{
	V3 Result = {(real32)From->X, (real32)From->Y, (real32)From->Z};
	return Result;
}