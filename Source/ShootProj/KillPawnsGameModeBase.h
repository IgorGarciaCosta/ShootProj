// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShootProjGameModeBase.h"
#include "KillPawnsGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTPROJ_API AKillPawnsGameModeBase : public AShootProjGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* PawnKilled) override;

};
