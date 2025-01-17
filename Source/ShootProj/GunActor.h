// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunActor.generated.h"

UCLASS()
class SHOOTPROJ_API AGunActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
		class USceneComponent* RootComp;

	


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class  USkeletalMeshComponent* Gun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UParticleSystem* GunParticleEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UParticleSystem* HitParticleEffect;

	UFUNCTION(BlueprintCallable)
	void GunShoot();

	void DestroyGun();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayParticles();

	UPROPERTY(EditAnywhere)
		float EndLocation = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float GunDamage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* ImpactSound;

	
};
