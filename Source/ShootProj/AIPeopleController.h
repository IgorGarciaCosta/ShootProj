// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIPeopleController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTPROJ_API AAIPeopleController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
private:
	//behavior trees
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* AIPeopleBehaviorTree;
	//vars
	UPROPERTY(EditAnywhere)
		FVector CharWalkDist;
};
