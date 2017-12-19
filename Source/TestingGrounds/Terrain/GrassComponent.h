// Copyright Nick Bellamy.

#pragma once

#include "CoreMinimal.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GrassComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGGROUNDS_API UGrassComponent : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrassComponent();

	// The bounds of the tile, set in blueprint
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FBox SpawningExtents;
	
	// How many instances of the mesh to spawn
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	int32 SpawnCount;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Method to spawn the grass
	void SpawnGrass();
	
};