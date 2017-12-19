// Copyright Nick Bellamy.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorPool.generated.h"

UCLASS()
class TESTINGGROUNDS_API UActorPool : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UActorPool();

	// Checkout an Actor from the pool
	AActor* Checkout();

	// Return an Actor to the pool
	void Return(AActor* ActorToReturn);
	
	// Add an Actor to the pool
	// TODO This logic may end up the same as Return(), so can consolidate
	void Add(AActor* ActorToAdd);

private:
	TArray<AActor*> Pool;
};
