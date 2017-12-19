// Copyright Nick Bellamy.

#include "ActorPool.h"


// Sets default values
UActorPool::UActorPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;

}

AActor* UActorPool::Checkout()
{
	// If there are no NavMeshBoundsVolumes in Pool return nullptr, else return a NavMeshBoundsVolume
	return Pool.Num() == 0 ? nullptr : Pool.Pop();
}

void UActorPool::Return(AActor* ActorToReturn)
{
	Add(ActorToReturn);
}

void UActorPool::Add(AActor* ActorToAdd)
{
	Pool.Push(ActorToAdd);
}

