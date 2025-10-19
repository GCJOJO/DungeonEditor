//  

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VoxelFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONEDITOR_API UVoxelFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintPure, Category="Voxel")
	static FIntVector WorldToBlockPosition(const FVector& Position);
	
	UFUNCTION(BlueprintPure, Category="Voxel")
	static FIntVector WorldToLocalBlockPosition(const FVector& Position, const int Size);

	UFUNCTION(BlueprintPure, Category="Voxel")
	static FIntVector WorldToChunkPosition(const FVector& Position, const int Size);
};
