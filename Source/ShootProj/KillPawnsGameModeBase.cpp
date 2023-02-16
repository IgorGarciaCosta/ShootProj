// Fill out your copyright notice in the Description page of Project Settings.


#include "KillPawnsGameModeBase.h"

void AKillPawnsGameModeBase::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	//UE_LOG(LogTemp, Warning, TEXT("police killed"));
	APlayerController* PlayerCont = Cast<APlayerController>(PawnKilled->GetController());
	//UE_LOG(LogTemp, Warning, TEXT("function called here (kill)"));

	if (PlayerCont!=nullptr) {
		//UE_LOG(LogTemp, Warning, TEXT("entered GameHasEnded (kill)"));
		PlayerCont->GameHasEnded(nullptr, false);
	}


}
