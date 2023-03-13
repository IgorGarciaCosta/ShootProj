// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	if (HUD != nullptr) {
		HUD->RemoveFromViewport();
	}
	UUserWidget* LoseScreen = CreateWidget(this, WBPLoseScreen);
	//UE_LOG(LogTemp, Warning, TEXT("Player was killed"));

	if (LoseScreen!=nullptr) {
		LoseScreen->AddToViewport();
	}
}

void AShooterPlayerController::BeginPlay()
{
	HUD = CreateWidget(this, HUDBP);

	if (HUD != nullptr) {
		HUD->AddToViewport();
	}
}
