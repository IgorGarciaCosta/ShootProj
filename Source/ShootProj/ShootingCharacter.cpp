// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingCharacter.h"
#include "GunActor.h"
#include "Kismet/GameplayStatics.h"
#include "ShootProjGameModeBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
AShootingCharacter::AShootingCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;



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

	if (CurrentHealth <= 0) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathEffect, GetTransform());
		GunSPawn->DestroyGun();
		Destroy();
		
	}

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
	PlayerInputComponent->BindAction(TEXT("ZoomCamera"), EInputEvent::IE_Pressed, this, &AShootingCharacter::ZoomIn);
	PlayerInputComponent->BindAction(TEXT("ZoomCamera"), EInputEvent::IE_Released, this, &AShootingCharacter::ZoomOut);

}

void AShootingCharacter::TakeDamageFromShoot(float RecDamage)
{

	if (CurrentHealth > 0) {
		CurrentHealth -= RecDamage;
		UE_LOG(LogTemp, Log, TEXT("CurrentHealth? %f"), CurrentHealth);
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

void AShootingCharacter::ZoomIn()
{
	FollowCamera->SetFieldOfView(45.f);
}

void AShootingCharacter::ZoomOut()
{
	FollowCamera->SetFieldOfView(90.f);
}

bool AShootingCharacter::IsDead() const
{
	return CurrentHealth <= 0;
}

float AShootingCharacter::GetHealthPercent() const
{
	return CurrentHealth / MaxHealth;
}

void AShootingCharacter::Shoot()
{
	if (IsValid(GunSPawn)) {
		GunSPawn->GunShoot();
		GunSPawn->PlayParticles();
	}
}

