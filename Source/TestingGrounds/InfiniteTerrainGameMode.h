// Copyright Nick Bellamy.

#pragma once

#include "CoreMinimal.h"
#include "TestingGroundsGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API AInfiniteTerrainGameMode : public ATestingGroundsGameMode
{
	GENERATED_BODY()
	
public:
	AInfiniteTerrainGameMode();

	// Populates a pool with Nav Mesh Bounds Volumes
	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateBoundsVolumePool();

protected:
	// Pointer to the NavMeshBoundsVolumePool
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
	class UActorPool* NavMeshBoundsVolumePool;
	
private:
	// Adds a NavMeshBoundsVolume to the pool
	void AddToPool(class ANavMeshBoundsVolume *VolumeToAdd);
	
};
