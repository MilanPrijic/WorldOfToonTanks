// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider")); // CreateDefaultSubobject is unreal specific function. It creates a new object and attaches it to the current object. It also sets the name of the object.
	RootComponent = CapsuleComponent; // Set the CapsuleComponent as the root component of the pawn.

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent); // Attach the BaseMesh to the root component.
	
	TurretMesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh); // Attach the TurretMesh to the BaseMesh.

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh); // Attach the ProjectileSpawnPoint to the TurretMesh.
	
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation(); // Get the vector from the turret to the target.
	FRotator LookAtRotation = ToTarget.Rotation();
	LookAtRotation.Pitch = 0; // Set the pitch to 0 so that the turret does not rotate up and down.
	LookAtRotation.Roll = 0; // Set the roll to 0 so that the turret does not rotate left and right.

	
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(),
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			25.f)); // Set the world rotation of the turret to the LookAtRotation.
}

void ABasePawn::Fire()
{
	// Get the projectile spawn point location and rotation.
	FVector ProjectileSpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator ProjectileSpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

	// DrawDebugSphere(GetWorld(), ProjectileSpawnLocation, 20.f, 12, FColor::Red, false, 3.0f);

	// Spawn the projectile.
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnLocation, ProjectileSpawnRotation);
	Projectile->SetOwner(this);
}

void ABasePawn::HandleDestruction()
{
	if (DeathParticles) {
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}
	if (DeathSound) {
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	}
	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(DeathCameraShakeClass);
	}
}


