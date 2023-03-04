// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	UUserWidget* LoseScreen = CreateWidget(this, WBPLoseScreen);
	//UE_LOG(LogTemp, Warning, TEXT("Player was killed"));

	if (LoseScreen!=nullptr) {
		LoseScreen->AddToViewport();
	}
}
