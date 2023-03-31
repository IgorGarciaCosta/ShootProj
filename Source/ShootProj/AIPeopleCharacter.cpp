// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPeopleCharacter.h"
#include "ShootProjGameModeBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AAIPeopleCharacter::AAIPeopleCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIPeopleCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurHealth = MaxHealth;
}

// Called every frame
void AAIPeopleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsDead()) {
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

// Called to bind functionality to input
void AAIPeopleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIPeopleCharacter::TakeDamageFromShoot(float RecDamage)
{
	UE_LOG(LogTemp, Warning, TEXT("called"));
	if (CurHealth > 0) {
		CurHealth -= RecDamage;
		UE_LOG(LogTemp, Log, TEXT("CurrentHealth: %f"), CurHealth);
	}

	else {
		UE_LOG(LogTemp, Warning, TEXT("Died"));
		IsDead();
	}

	if (IsDead()) {
		AShootProjGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AShootProjGameModeBase>();

		if (GameMode != nullptr) {
			//UE_LOG(LogTemp, Warning, TEXT("char shoot to kill"));
			GameMode->PawnKilled(this);
		}

	}
}

bool AAIPeopleCharacter::IsDead() const
{
	return CurHealth<=0.f;
}

