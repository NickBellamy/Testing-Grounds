// Copyright Nick Bellamy.

#include "Tile.h"
#include "Engine/World.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Spawn a number of instances of specified actors (ToSpawn) between MinSpawn and MaxSpawn
void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn, int32 MaxSpawn)
{
	// Set bounds of spawn locations
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);

	// Calculate random number of actors to spawn
	int32 NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		// Create random spawn point within box bounds
		FVector SpawnPoint = FMath::RandPointInBox(Bounds);
		// Spawn actor
		AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
		// Move actor to SpawnPoint
		Spawned->SetActorRelativeLocation(SpawnPoint);
		// Attach spawned object to the floor
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}
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

