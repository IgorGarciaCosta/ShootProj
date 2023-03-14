// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShootingCharacter.generated.h"

UCLASS()
class SHOOTPROJ_API AShootingCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShootingCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void TakeDamageFromShoot(float RecDamage);

	float ReceivedDamage = 10.f;

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere)
	float CurrentHealth = MaxHealth;

	UFUNCTION(BlueprintPure)
		bool IsDead() const;


	UFUNCTION(BlueprintPure)
		float GetHealthPercent() const;

private:
	class AGunActor* GunSPawn;
	void MoveForward(float val);
	void MoveRight(float val);
	void LookUp(float val);
	void LookRight(float val);
	void ZoomIn();
	void ZoomOut();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UParticleSystem* DeathEffect;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AGunActor> GunBPClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;




	void Shoot();

};
