// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CarClass.generated.h"

UCLASS()
class SHOOTPROJ_API ACarClass : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACarClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void TakeDamageFromShoot(float RecDamage);

	UFUNCTION(BlueprintPure)
		bool IsDead() const;

	void Move(float MoveValue);
	void Turn(float TurnValue);
	//void RollControl(float roll);

	float CarSpeed = 600.f;
	float CarTurnRate = 45.f;

private:
	float MaxHealth = 200.f;
	float CurHealth = MaxHealth;

public:
	//emitters
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UParticleSystem* CarEmitter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UParticleSystem* CarDamageEmitter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USoundBase* CarExplosionSound;
};
