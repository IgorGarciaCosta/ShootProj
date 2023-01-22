// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingCharacter.h"
#include "GunActor.h"

// Sets default values
AShootingCharacter::AShootingCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShootingCharacter::BeginPlay()
{
	Super::BeginPlay();
	GunSPawn = GetWorld()->SpawnActor<AGunActor>(GunBPClass);
	GunSPawn->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, "GunSocket_r");
	
	GunSPawn->SetOwner(this);

}

// Called every frame
void AShootingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShootingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShootingCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShootingCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShootingCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AShootingCharacter::LookRight);
	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShootingCharacter::Shoot);

}

void AShootingCharacter::MoveForward(float val)
{
	AddMovementInput(GetActorForwardVector(), val, IsMoveInputIgnored());
}

void AShootingCharacter::MoveRight(float val)
{
	AddMovementInput(GetActorRightVector(), val, IsMoveInputIgnored());

}

void AShootingCharacter::LookUp(float val)
{
	AddControllerPitchInput(val);
}

void AShootingCharacter::LookRight(float val)
{
	AddControllerYawInput(val);
}

void AShootingCharacter::Shoot()
{
	if (IsValid(GunSPawn)) {
		GunSPawn->GunShoot();
	}
}

