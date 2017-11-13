// Copyright Nick Bellamy.

#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the patrol route
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	UPatrolRoute* PatrolRoute = ControlledPawn->FindComponentByClass<class UPatrolRoute>();
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	// Set patrol points to a local variable
	TArray<AActor*> PatrolPoints = PatrolRoute->GetPatrolPoints();

	// Protect and warn about empty patrol routes
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No patrol points found for: %s"), *ControlledPawn->GetName());
		return EBTNodeResult::Failed;
	}

	// Set waypoint of the current Index
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);	// Gets current index from IndexKey, initial value will be 0
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);	// Sets NextWaypoint as the object at this index
	
	// Cycle index
	int32 NewIndex = ++Index % PatrolPoints.Num();	// Modulus used so NewIndex will always be between 0 and size of patrol points -1
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NewIndex);	// Sets NewIndex value
	
	return EBTNodeResult::Succeeded;

}