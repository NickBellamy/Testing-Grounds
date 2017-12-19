// Copyright Nick Bellamy.

#include "ActorPool.h"


// Sets default values
AActorPool::AActorPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActorPool::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

