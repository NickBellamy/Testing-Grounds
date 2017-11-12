// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrollingGuard.h"	// TODO Remove coupling

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//TODO Protect against empty patrol routes

	// Get the patrol points and set as local array variable
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	APatrollingGuard* PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	TArray<AActor*> PatrolPoints = PatrollingGuard->PatrolPoints_CPP;

	// Set waypoint of the current Index
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);	// Gets current index from IndexKey, initial value will be 0
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);	// Sets NextWaypoint as the object at this index
	
	// Cycle index
	int32 NewIndex = ++Index % PatrolPoints.Num();	// Modulus used so NewIndex will always be between 0 and size of patrol points -1
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NewIndex);	// Sets NewIndex value
	
	return EBTNodeResult::Succeeded;

}