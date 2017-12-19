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
	// TODO Remove diagnostic log
	UE_LOG(LogTemp, Warning, TEXT("[%s] Checkout"), *GetName());
	
	// TODO Write logic to checkout Actor
	return nullptr;
}

void UActorPool::Return(AActor* ActorToReturn)
{
	// Pointer protection
	if (ActorToReturn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] Returned null actor."), *GetName());
		return;
	}
	// TODO Remove diagnostic log
	UE_LOG(LogTemp, Warning, TEXT("[%s] Returned: {%s}."), *GetName(), *ActorToReturn->GetName());

	// TODO Write logic to return an Actor to the pool
}

void UActorPool::Add(AActor* ActorToAdd)
{
	// TODO Write logic to add an actor to the pool
}

