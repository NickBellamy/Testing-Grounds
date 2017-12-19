// Copyright Nick Bellamy.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class UActorPool;

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Terrain")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 500, float MinScale = 1, float MaxScale = 1);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called before the object is destroyed
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Set the pool reference
	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* InPool);

private:
	bool FindEmptyLocation(FVector& OutLocation, float Radius);

	// Place an Actor on the tile
	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation, float Scale);

	// Check to see if an actor has enough room to spawn at location without clipping
	bool CanSpawnAtLocation(FVector Location, float Radius);
	
	// Reference to the Pool of Navmeshes
	UActorPool* Pool;

	// Checks out a NavMeshBoundsVolume and sets its position to that of the tile
	void PositionNavMeshBoundsVolume();

	// Pointer to the checked out NavMeshBoundsVolume
	AActor* NavMeshBoundsVolume = nullptr;
};
