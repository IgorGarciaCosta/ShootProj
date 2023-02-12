// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_Shoot.h"
#include "ShootingCharacter.h"
#include "AIController.h"

UMyBTTask_Shoot::UMyBTTask_Shoot()
{
	NodeName = TEXT("Shoot");


}

EBTNodeResult::Type UMyBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;

	AShootingCharacter* Character =Cast<AShootingCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(Character==nullptr)  return EBTNodeResult::Failed;

	Character->Shoot();
	
	return EBTNodeResult::Succeeded;
}
