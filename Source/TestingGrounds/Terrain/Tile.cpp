// Copyright Nick Bellamy.

#include "Tile.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Spawn a number of instances of specified actors (ToSpawn) between MinSpawn and MaxSpawn
void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius)
{
	// Calculate random number of actors to spawn
	int32 NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnPoint;
		bool isFound = FindEmptyLocation(SpawnPoint, Radius);
		if (isFound)
		{
			float RandomRotation = FMath::RandRange(-180.0f, 180.0f);
			PlaceActor(ToSpawn, SpawnPoint, RandomRotation);
		}
	}
}

bool ATile::FindEmptyLocation(FVector& OutLocation, float Radius)
{
	// Set bounds of spawn locations
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);

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

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation)
{
	// Spawn actor
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	// Move actor to SpawnPoint
	Spawned->SetActorRelativeLocation(SpawnPoint);
	// Set Actor Rotation
	Spawned->SetActorRotation(FRotator(0, Rotation, 0));
	// Attach spawned object to the floor
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
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
	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	DrawDebugCapsule(GetWorld(), GlobalLocation, 0, Radius, FQuat::Identity,	 ResultColor, true, 100);
	return !HasHit;
}
