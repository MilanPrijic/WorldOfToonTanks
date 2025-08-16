// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RotateTurret(FVector LookAtTarget);

	void Fire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	// UPROPERTY(VisibleDefaultsOnly) // This property will be visible in the blueprint editor but not editable. Its won't be visible on instance (when actor is place in the world).
	// int32 VisibleDefaultOnlyInt = 5;
	//
	// UPROPERTY(EditDefaultsOnly) // This property can be edited in the blueprint editor only. It won't be visible on instance (when actor is place in the world).
	// int32 EditDefaultsOnlyInt = 10;
	//
	// UPROPERTY(EditInstanceOnly) // This property is only editable in the instance (when actor is place in the world). It won't be visible in the blueprint editor.
	// int32 EditInstanceOnlyInt = 15;
	//
	// // VisibleAnywhere and EditAnywhere are not allowed to be private.
	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true")) // BlueprintReadWrite is used to make the property visible in the blueprint editor and also editable.
	// int32 VisibleAnywhereInt = 20;
	//
	// UPROPERTY(EditAnywhere)
	// float Speed = 400.f;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent; // IMPORTANT: Use "class" keyword to avoid importing whole UCapsuleComponent.h file. This is a "forward declaration". This header file does not need to know the details of UCapsuleComponent, just that it exists. In other words we import only when we need to use implementation details of UCapsuleComponent.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category="Combat")
	UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category="Combat")
	USoundBase* DeathSound;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
	
};
