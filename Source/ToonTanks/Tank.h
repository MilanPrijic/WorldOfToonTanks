// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HandleDestruction();
	
	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

	bool bAlive = true;

private:

	UPROPERTY(VisibleAnywhere, Category="Components") // when you are not exposing the variable to event graph, you dont need meta=(AllowPrivateAccess = "true")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category="Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category="Movement")
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, Category="Movement")
	float TurnRate = 100.f;

	void Move(float Value);
	void Rotate(float Value);

	APlayerController* TankPlayerController;
};
