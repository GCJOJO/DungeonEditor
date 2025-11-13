//  

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Dungeon/DungeonEnums.h"
#include "Dungeon/ChunkMeshData.h"

#include "DungeonMesh.generated.h"

class UProceduralMeshComponent;

UCLASS()
class DUNGEONEDITOR_API ADungeonMesh : public AActor
{
	GENERATED_BODY()
	
	struct FMask
	{
		EVoxelBlock Block;
		int Normal;
	};

public:	
	// Sets default values for this actor's properties
	ADungeonMesh();

	UPROPERTY(EditAnywhere, BlueprintSetter = SetSize, BlueprintGetter = GetSize, Category = "Dungeon")
	int Size = 98;

	UPROPERTY(EditInstanceOnly, Category="Chunk")
	TObjectPtr<UMaterialInterface> Material;

	UFUNCTION(BlueprintCallable, Category="Dungeon")
	void ModifyVoxel(const FIntVector Position, const EVoxelBlock Block);

	UFUNCTION(BlueprintCallable, Category="Dungeon")
	void ModifyVoxelArea(const FIntVector From, const FIntVector To, const EVoxelBlock Block);

	UFUNCTION(BlueprintCallable, Category="Dungeon")
	void PushVoxel(const FIntVector Position, const EVoxelBlock Block);

	UFUNCTION(BlueprintCallable, Category="Dungeon")
	void PushVoxelArea(const FIntVector From, const FIntVector To, const EVoxelBlock Block);

	UFUNCTION(BlueprintCallable, Category="Dungeon")
	void ApplyVoxels();

	UFUNCTION(BlueprintCallable)
	void SetSize(int newSize)
	{
		Size = newSize;
		ClearMesh();
		Setup();
		GenerateMesh();
		ApplyMesh();
	}

	UFUNCTION(BlueprintPure)
	int GetSize() const
	{
		return Size;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Setup();

	void GenerateMesh();

	TObjectPtr<UProceduralMeshComponent> Mesh;
	FMeshData MeshData;
	int VertexCount = 0;

	bool isDirty = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ApplyMesh() const;
	void ClearMesh();

	virtual void ModifyVoxelData(const FIntVector Position, const EVoxelBlock Block);

	TArray<EVoxelBlock> Blocks;

	void CreateQuad(FMask Mask, FIntVector AxisMask, int Width, int Height, FIntVector V1, FIntVector V2, FIntVector V3, FIntVector V4);
	int GetBlockIndex(int X, int Y, int Z) const;
	EVoxelBlock GetBlock(FIntVector Index) const;
	bool CompareMask(FMask M1, FMask M2) const;
	int GetTextureIndex(EVoxelBlock Block, FVector Normal) const;
};
