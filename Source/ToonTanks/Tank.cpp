// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	// PlayerControllerRef = UGameplayStatics::GetPlayerController(this, 0);

	TankPlayerController = Cast<APlayerController>(GetController());
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (TankPlayerController)
	{
		FHitResult HitResult;
		bool HasHit = TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 20.f, 12, FColor::Red, false, -1.0f);

		if (HasHit)
		{
			RotateTurret(HitResult.ImpactPoint);
		}
	}

}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Rotate);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float Value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	DeltaLocation.X = Value * Speed * DeltaTime;
	AddActorLocalOffset(DeltaLocation, true);
	// UE_LOG(LogTemp, Warning, TEXT("Move Forward: %f"), Value);
}

void ATank::Rotate(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	DeltaRotation.Yaw = Value * TurnRate * DeltaTime;
	AddActorLocalRotation(DeltaRotation, true);
	// UE_LOG(LogTemp, Warning, TEXT("Rotate: %f"), Value);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}




