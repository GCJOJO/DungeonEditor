//  


#include "Dungeon/DungeonMesh.h"
#include "ProceduralMeshComponent.h"

// Sets default values
ADungeonMesh::ADungeonMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>("Mesh");

	// Mesh Settings
	Mesh->SetCastShadow(true);

	// Set Mesh as root
	SetRootComponent(Mesh);

	Setup();
}

// Called when the game starts or when spawned
void ADungeonMesh::BeginPlay()
{
	Super::BeginPlay();
	
	Setup();
	GenerateMesh();
	UE_LOG(LogTemp, Warning, TEXT("Vertex Count : %d"), VertexCount);
	ApplyMesh();
}

void ADungeonMesh::Setup()
{
	// Initialize Blocks
	Blocks.Reset();
	Blocks.SetNumZeroed(Size * Size * Size);
}

// Called every frame
void ADungeonMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADungeonMesh::ApplyMesh() const
{
	Mesh->SetMaterial(0, Material);
	Mesh->CreateMeshSection(
		0,
		MeshData.Vertices,
		MeshData.Triangles,
		MeshData.Normals,
		MeshData.UV0,
		MeshData.Colors,
		TArray<FProcMeshTangent>(),
		true
	);
}

void ADungeonMesh::ClearMesh()
{
	VertexCount = 0;
	MeshData.Clear();
}

void ADungeonMesh::ModifyVoxel(const FIntVector Position, const EVoxelBlock Block)
{
	if (Position.X >= Size || Position.Y >= Size || Position.Z >= Size || Position.X < 0 || Position.Y < 0 || Position.Z < 0) return;

	ModifyVoxelData(Position, Block);

	ClearMesh();
	GenerateMesh();
	ApplyMesh();
}

void ADungeonMesh::ModifyVoxelArea(const FIntVector From, const FIntVector To, const EVoxelBlock Block)
{
	UE_LOG(LogTemp, Warning, TEXT("From : (%d; %d; %d), To : (%d; %d; %d)"), From.X, From.Y, From.Z, To.X, To.Y, To.Z);
	int sizeX = To.X - From.X;
	int sizeY = To.Y - From.Y;
	int sizeZ = To.Z - From.Z;

	if (sizeX % 2 == 1) sizeX++;
	if (sizeY % 2 == 1) sizeY++;
	if (sizeZ % 2 == 1) sizeZ++;

	for(int x = 0; x <= sizeX + 1; x++)
	{
		for (int y = 0; y <= sizeY + 1; y++)
		{
			for (int z = 0; z <= sizeZ + 1; z++)
			{
				FIntVector position;
				position.X = From.X + x;
				position.Y = From.Y + z;
				position.Z = From.Z + y;

				if (position.X >= Size || position.Y >= Size || position.Z >= Size || position.X < 0 || position.Y < 0 || position.Z < 0) continue;

				ModifyVoxelData(position, Block);
			}
		}
	}

	ClearMesh();
	GenerateMesh();
	ApplyMesh();
}

void ADungeonMesh::PushVoxel(const FIntVector Position, const EVoxelBlock Block)
{
	if (Position.X >= Size || Position.Y >= Size || Position.Z >= Size || Position.X < 0 || Position.Y < 0 || Position.Z < 0) return;

	ModifyVoxelData(Position, Block);

	isDirty = true;
}

void ADungeonMesh::PushVoxelArea(const FIntVector From, const FIntVector To, const EVoxelBlock Block)
{
	//UE_LOG(LogTemp, Warning, TEXT("From : (%d; %d; %d), To : (%d; %d; %d)"), From.X, From.Y, From.Z, To.X, To.Y, To.Z);
	int sizeX = To.X - From.X;
	int sizeY = To.Y - From.Y;
	int sizeZ = To.Z - From.Z;

	if (sizeX % 2 == 1) sizeX++;
	if (sizeY % 2 == 1) sizeY++;
	if (sizeZ % 2 == 1) sizeZ++;

	for (int x = 0; x <= sizeX + 1; x++)
	{
		for (int y = 0; y <= sizeY + 1; y++)
		{
			for (int z = 0; z <= sizeZ + 1; z++)
			{
				FIntVector position;
				position.X = From.X + x;
				position.Y = From.Y + z;
				position.Z = From.Z + y;

				if (position.X >= Size || position.Y >= Size || position.Z >= Size || position.X < 0 || position.Y < 0 || position.Z < 0) continue;

				ModifyVoxelData(position, Block);
			}
		}
	}

	isDirty = true;
}

void ADungeonMesh::ApplyVoxels()
{
	if (isDirty)
	{
		ClearMesh();
		GenerateMesh();
		ApplyMesh();
		isDirty = false;
	}
}

void ADungeonMesh::GenerateMesh()
{
	// Sweep over each axis (X, Y, Z)
	for (int Axis = 0; Axis < 3; ++Axis)
	{
		// 2 Perpendicular axis
		const int Axis1 = (Axis + 1) % 3;
		const int Axis2 = (Axis + 2) % 3;

		const int MainAxisLimit = Size;
		const int Axis1Limit = Size;
		const int Axis2Limit = Size;

		auto DeltaAxis1 = FIntVector::ZeroValue;
		auto DeltaAxis2 = FIntVector::ZeroValue;

		auto ChunkItr = FIntVector::ZeroValue;
		auto AxisMask = FIntVector::ZeroValue;

		AxisMask[Axis] = 1;

		TArray<FMask> Mask;
		Mask.SetNum(Axis1Limit * Axis2Limit);

		// Check each slice of the chunk
		for (ChunkItr[Axis] = -1; ChunkItr[Axis] < MainAxisLimit;)
		{
			int N = 0;

			// Compute Mask
			for (ChunkItr[Axis2] = 0; ChunkItr[Axis2] < Axis2Limit; ++ChunkItr[Axis2])
			{
				for (ChunkItr[Axis1] = 0; ChunkItr[Axis1] < Axis1Limit; ++ChunkItr[Axis1])
				{
					const auto CurrentBlock = GetBlock(ChunkItr);
					const auto CompareBlock = GetBlock(ChunkItr + AxisMask);

					const bool CurrentBlockOpaque = CurrentBlock != EVoxelBlock::Air;
					const bool CompareBlockOpaque = CompareBlock != EVoxelBlock::Air;

					if (CurrentBlockOpaque == CompareBlockOpaque)
					{
						Mask[N++] = FMask{ EVoxelBlock::Null, 0 };
					}
					else if (CurrentBlockOpaque)
					{
						Mask[N++] = FMask{ CurrentBlock, 1 };
					}
					else
					{
						Mask[N++] = FMask{ CompareBlock, -1 };
					}
				}
			}

			++ChunkItr[Axis];
			N = 0;

			// Generate Mesh From Mask
			for (int j = 0; j < Axis2Limit; ++j)
			{
				for (int i = 0; i < Axis1Limit;)
				{
					if (Mask[N].Normal != 0)
					{
						const auto CurrentMask = Mask[N];
						ChunkItr[Axis1] = i;
						ChunkItr[Axis2] = j;

						int Width;

						for (Width = 1; i + Width < Axis1Limit && CompareMask(Mask[N + Width], CurrentMask); ++Width)
						{
						}

						int Height;
						bool Done = false;

						for (Height = 1; j + Height < Axis2Limit; ++Height)
						{
							for (int k = 0; k < Width; ++k)
							{
								if (CompareMask(Mask[N + k + Height * Axis1Limit], CurrentMask)) continue;

								Done = true;
								break;
							}

							if (Done) break;
						}

						DeltaAxis1[Axis1] = Width;
						DeltaAxis2[Axis2] = Height;

						CreateQuad(
							CurrentMask, AxisMask, Width, Height,
							ChunkItr,
							ChunkItr + DeltaAxis1,
							ChunkItr + DeltaAxis2,
							ChunkItr + DeltaAxis1 + DeltaAxis2
						);

						DeltaAxis1 = FIntVector::ZeroValue;
						DeltaAxis2 = FIntVector::ZeroValue;

						for (int l = 0; l < Height; ++l)
						{
							for (int k = 0; k < Width; ++k)
							{
								Mask[N + k + l * Axis1Limit] = FMask{ EVoxelBlock::Null, 0 };
							}
						}

						i += Width;
						N += Width;
					}
					else
					{
						i++;
						N++;
					}
				}
			}
		}
	}
}

void ADungeonMesh::CreateQuad(
	const FMask Mask,
	const FIntVector AxisMask,
	const int Width,
	const int Height,
	const FIntVector V1,
	const FIntVector V2,
	const FIntVector V3,
	const FIntVector V4
)
{
	const auto Normal = FVector(AxisMask * Mask.Normal);
	const auto Color = FColor(0, 0, 0, GetTextureIndex(Mask.Block, Normal));

	MeshData.Vertices.Append({
		FVector(V1) * 100,
		FVector(V2) * 100,
		FVector(V3) * 100,
		FVector(V4) * 100
		});

	MeshData.Triangles.Append({
		VertexCount,
		VertexCount + 2 + Mask.Normal,
		VertexCount + 2 - Mask.Normal,
		VertexCount + 3,
		VertexCount + 1 - Mask.Normal,
		VertexCount + 1 + Mask.Normal
		});

	MeshData.Normals.Append({
		Normal,
		Normal,
		Normal,
		Normal
		});

	MeshData.Colors.Append({
		Color,
		Color,
		Color,
		Color
		});

	if (Normal.X == 1 || Normal.X == -1)
	{
		MeshData.UV0.Append({
			FVector2D(Width, Height),
			FVector2D(0, Height),
			FVector2D(Width, 0),
			FVector2D(0, 0),
			});
	}
	else
	{
		MeshData.UV0.Append({
			FVector2D(Height, Width),
			FVector2D(Height, 0),
			FVector2D(0, Width),
			FVector2D(0, 0),
			});
	}

	VertexCount += 4;
}

void ADungeonMesh::ModifyVoxelData(const FIntVector Position, const EVoxelBlock Block)
{
	const int Index = GetBlockIndex(Position.X, Position.Y, Position.Z);

	if (Index < 0 || Index > Blocks.Max() - 1) return;

	Blocks[Index] = Block;
}

int ADungeonMesh::GetBlockIndex(const int X, const int Y, const int Z) const
{
	return Z * Size * Size + Y * Size + X;
}

EVoxelBlock ADungeonMesh::GetBlock(const FIntVector Index) const
{
	if (Index.X >= Size || Index.Y >= Size || Index.Z >= Size || Index.X < 0 || Index.Y < 0 || Index.Z < 0)
		return EVoxelBlock::Air;
	return Blocks[GetBlockIndex(Index.X, Index.Y, Index.Z)];
}

bool ADungeonMesh::CompareMask(const FMask M1, const FMask M2) const
{
	return M1.Block == M2.Block && M1.Normal == M2.Normal;
}

int ADungeonMesh::GetTextureIndex(const EVoxelBlock Block, const FVector Normal) const
{
	switch (Block) {
	case EVoxelBlock::Wall:
	{
		if (Normal == FVector::UpVector || Normal == FVector::DownVector) return 0;
		return 2;
	}
	case EVoxelBlock::Floor: return 3;
	default: return 255;
	}
}