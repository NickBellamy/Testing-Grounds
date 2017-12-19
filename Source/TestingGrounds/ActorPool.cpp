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
	// TODO Write logic to checkout Actor
	return nullptr;
}

void UActorPool::Return(AActor* ActorToReturn)
{
	// TODO Write logic to return an Actor to the pool
}

void UActorPool::Add(AActor* ActorToAdd)
{
	// TODO Write logic to add an actor to the pool
}

