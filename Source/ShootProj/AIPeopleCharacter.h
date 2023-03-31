// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIPeopleCharacter.generated.h"

UCLASS()
class SHOOTPROJ_API AAIPeopleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIPeopleCharacter();

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
private:
	float MaxHealth = 200.f;
	float CurHealth;
};
