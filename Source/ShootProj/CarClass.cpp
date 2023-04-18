// Fill out your copyright notice in the Description page of Project Settings.


#include "CarClass.h"
#include "Kismet/GameplayStatics.h"
#include "ShootProjGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
ACarClass::ACarClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACarClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACarClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurHealth <= 60) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CarDamageEmitter, GetActorLocation());

	}
	if (IsDead()) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CarEmitter, GetActorLocation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), CarExplosionSound, GetActorLocation());
		Destroy();
	}
}

// Called to bind functionality to input
void ACarClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForwardBackward"), this, &ACarClass::Move);
	PlayerInputComponent->BindAxis(TEXT("CarTurn"), this, &ACarClass::Turn);
	//PlayerInputComponent->BindAxis(TEXT("RollControl"), this, &ACarClass::RollControl);

}

void ACarClass::TakeDamage(float RecDamage)
{
	//UE_LOG(LogTemp, Warning, TEXT("called"));
	if (CurHealth > 0) {
		CurHealth -= RecDamage;
		//UE_LOG(LogTemp, Log, TEXT("CurrentHealth: %f"), CurHealth);
	}

	else {
		//UE_LOG(LogTemp, Warning, TEXT("Died"));
		IsDead();
	}

}

bool ACarClass::IsDead() const
{
	return CurHealth <= 0.f;
}

void ACarClass::Move(float MoveValue)
{
	FVector CarLoc(0.f);
	CarLoc.X = MoveValue * CarSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(CarLoc, true);
}

void ACarClass::Turn(float TurnValue)
{
	float CarRotator = TurnValue*CarTurnRate* UGameplayStatics::GetWorldDeltaSeconds(this);
	//AddActorLocalRotation(CarRotator);
	AddControllerYawInput(CarRotator);
}

//void ACarClass::RollControl(float roll)
//{
//	FRotator CarRoll(0);
//	CarRoll.Pitch = roll*30* UGameplayStatics::GetWorldDeltaSeconds(this);
//	AddActorLocalRotation(CarRoll);
//}

