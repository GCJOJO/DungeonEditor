#pragma once

UENUM(BlueprintType)
enum class EVoxelDirection : uint8
{
	Forward, Right, Back, Left, Up, Down
};

UENUM(BlueprintType)
enum class EVoxelBlock : uint8
{
	Null, Air, Wall, Floor
};