// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->MaxSpeed = 2000.f;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particles"));
	TrailParticles->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation(), GetActorRotation());
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile:: OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// UE_LOG(LogTemp, Warning, TEXT("HIT"));
	// UE_LOG(LogTemp, Warning, TEXT("Hit Component name: %s"), *HitComponent->GetName());
	// UE_LOG(LogTemp, Warning, TEXT("Hit Other Actor name: %s"), *OtherActor->GetName());
	// UE_LOG(LogTemp, Warning, TEXT("Hit Other Component name: %s"), *OtherComponent->GetName());
	
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		Destroy();
		return;
	}
	
	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		if (HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation()); //spawn particles animation after projectile hits
		}
		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation(), GetActorRotation());
		}
		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(HitCameraShakeClass);
		}
	}

	Destroy();
	
}

