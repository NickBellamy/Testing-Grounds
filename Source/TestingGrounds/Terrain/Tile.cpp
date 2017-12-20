// Copyright Nick Bellamy.

#include "Tile.h"
#include "ActorPool.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Engine/World.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sets central point of navmesh with appropriate values for current tile size
	NavigationBoundsOffset = FVector(2000, 0, 0);

	// Set default values appropriate for current tile size
	MinExtent = FVector(0, -2000, 0);
	MaxExtent = FVector(4000, 2000, 0);

}

void ATile::SetPool(UActorPool* InPool)
{
	// TODO Remove debugging text
	UE_LOG(LogTemp, Warning, TEXT("[%s] Setting Pool %s"), *(this->GetName()), *(InPool->GetName()));
	
	// Set Pool
	Pool = InPool;

	PositionNavMeshBoundsVolume();
}

void ATile::PositionNavMeshBoundsVolume()
{
	// Checkout NavMeshBoundsVolume from pool
	NavMeshBoundsVolume = Pool->Checkout();

	// Pointer protection
	if (NavMeshBoundsVolume == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] Not enough actors in pool"), *GetName());
		return;
	}

	// TODO Remove diagnostic log
	UE_LOG(LogTemp, Warning, TEXT("[%s] Checked out: {%s}"), *GetName(), *NavMeshBoundsVolume->GetName());

	// Set location of NavMeshBoundsVolume to the location of the current tile
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);

	// Rebuild NavMesh
	GetWorld()->GetNavigationSystem()->Build();
}

// Spawn a number of instances of specified actors (ToSpawn) between MinSpawn and MaxSpawn
void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	// Array of spawn positions
	TArray<FSpawnPosition> SpawnPositions = RandomSpawnPositions(MinSpawn, MaxSpawn, Radius, MinScale, MaxScale);

	for (FSpawnPosition SpawnPosition : SpawnPositions)
	{
		PlaceActor(ToSpawn, SpawnPosition);
	}
}

// Spawn a number of instances of specified AI Pawns between MinSpawn and MaxSpawn
void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius)
{
	// Array of spawn positions
	TArray<FSpawnPosition> SpawnPositions = RandomSpawnPositions(MinSpawn, MaxSpawn, Radius, 1, 1);

	for (FSpawnPosition SpawnPosition : SpawnPositions)
	{
		PlaceAIPawn(ToSpawn, SpawnPosition);
	}

}

TArray<FSpawnPosition> ATile::RandomSpawnPositions(int32 MinSpawn, int32 MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	TArray<FSpawnPosition> SpawnPositions;

	// Calculate random number of actors to spawn
	int32 NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);
		bool isFound = FindEmptyLocation(SpawnPosition.Location, Radius * SpawnPosition.Scale);
		if (isFound)
		{
			SpawnPosition.Rotation = FMath::RandRange(-180.0f, 180.0f);
			SpawnPositions.Add(SpawnPosition);
		}
	}

	return SpawnPositions;
}

bool ATile::FindEmptyLocation(FVector& OutLocation, float Radius)
{
	// Set bounds of spawn locations
	FBox Bounds(MinExtent, MaxExtent);

	const int MAX_ATTEMPTS = 100;
	for (size_t i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector CandidatePoint = FMath::RandPointInBox(Bounds);
		if (CanSpawnAtLocation(CandidatePoint, Radius))
		{
			OutLocation = CandidatePoint;
			return true;
		}
	}
	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition)
{
	// Spawn actor
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	// Move actor to SpawnPoint
	Spawned->SetActorRelativeLocation(SpawnPosition.Location);
	// Set Actor Rotation
	Spawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
	// Set Actor Scale
	Spawned->SetActorScale3D(FVector(SpawnPosition.Scale));
	// Attach spawned object to the floor
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
}

void ATile::PlaceAIPawn(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition)
{
	// Spawn actor
	APawn* Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn);
	// Move actor to SpawnPoint
	Spawned->SetActorRelativeLocation(SpawnPosition.Location);
	// Set Actor Rotation
	Spawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
	// Attach spawned object to the floor
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	// Spawn AI Controller
	Spawned->SpawnDefaultController();
	// Add the "Enemy" tag
	Spawned->Tags.Add(FName("Enemy"));
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called before the tile is destroyed
void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Pool->Return(NavMeshBoundsVolume);

}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLocation,
		GlobalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);
	return !HasHit;
}
