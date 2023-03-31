// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPeopleController.h"
#include"BehaviorTree/BehaviorTreeComponent.h"
#include"BehaviorTree/BlackboardComponent.h"

void AAIPeopleController::BeginPlay()
{
	Super::BeginPlay();
	if (AIPeopleBehaviorTree != nullptr) {
		RunBehaviorTree(AIPeopleBehaviorTree);
	}

	FVector ActorStartLoc = GetPawn()->GetActorLocation();

	GetBlackboardComponent()->SetValueAsVector(TEXT("ActorStartLoc"), ActorStartLoc);

	ActorStartLoc += CharWalkDist;
	GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLoc"), ActorStartLoc);
}
