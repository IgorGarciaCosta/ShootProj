// Fill out your copyright notice in the Description page of Project Settings.


#include "GunActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShootingCharacter.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGunActor::AGunActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	SetRootComponent(RootComp);

	Gun = CreateDefaultSubobject<USkeletalMeshComponent>("Gun");
	Gun->SetupAttachment(RootComp);
	


}

// Called when the game starts or when spawned
void AGunActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunActor::GunShoot()
{
	UE_LOG(LogTemp, Warning, TEXT("Shoot"));
	//UGameplayStatics::SpawnEmitterAttached(GunParticleEffect, Gun, TEXT("b_gun_muzzleflash"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Gun, TEXT("MuzzleFlash"));
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	
	if (OwnerPawn == nullptr)return;

	AController* OwnerController = OwnerPawn->GetController();
	
	if (OwnerController == nullptr) return;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * 1000.f;

	FHitResult HitLocation;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	bool bDone = GetWorld()->LineTraceSingleByChannel(HitLocation, Location+40.f, End, ECollisionChannel::ECC_GameTraceChannel1, Params);

	if (bDone) {
		UGameplayStatics::SpawnSoundAtLocation(this, ImpactSound, HitLocation.Location);
		FVector ShotDirection = -Rotation.Vector();
		//DrawDebugPoint(GetWorld(), HitLocation.Location, 30.f, FColor::Green, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticleEffect, HitLocation.Location, ShotDirection.Rotation(), true);
	

		AShootingCharacter* HitActor = Cast<AShootingCharacter>(HitLocation.GetActor());

		if (HitActor != nullptr) {
			HitActor->TakeDamageFromShoot(10.f);
		}

	}
}

void AGunActor::DestroyGun()
{
	Destroy();
}

