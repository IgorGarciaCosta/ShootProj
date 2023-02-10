// Fill out your copyright notice in the Description page of Project Settings.


#include "AIShooterController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AAIShooterController::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (AIBehaviorTree != nullptr) {
		RunBehaviorTree(AIBehaviorTree);
	}

	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLoc"), PlayerPawn->GetActorLocation());
	
	GetBlackboardComponent()->SetValueAsVector(TEXT("PawnLocation"), GetPawn()->GetActorLocation());
}

void AAIShooterController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	bool IsIsLineOfSightTo = LineOfSightTo(PlayerPawn);
	/*if (IsIsLineOfSightTo) {
		MoveToActor(PlayerPawn, 150.f);
		SetFocus(PlayerPawn);
	}
	else {
		ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();
	}*/
	

}
