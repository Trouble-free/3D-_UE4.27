// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "MyMovementComponent.h"
#include "FollowingActor.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetNotifyRigidBodyCollision(true);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(Mesh);
	CameraBoom->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->TargetOffset = FVector(0, 0, 200.0f);
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 3.f;
	CameraBoom->bUsePawnControlRotation = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	MovementComp = CreateDefaultSubobject<UMyMovementComponent>(TEXT("MovementComp"));
	MovementComp->UpdatedComponent = RootComponent;

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	if (Follower)
	{
		Follower->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	}
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FVector NewLocation = GetActorLocation() + CurrentVelocity * DeltaTime;
	//SetActorLocation(NewLocation);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPawn::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AMyPawn::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyPawn::LookUp);

}

UPawnMovementComponent* AMyPawn::GetMovementComponent() const
{
	return MovementComp;
}

void AMyPawn::MoveForward(float Value)
{
	//CurrentVelocity.X += FMath::Clamp(Value, -1.f, 1.f) * MaxSpeed;
	if (MovementComp)
	{
		MovementComp->AddInputVector(GetActorForwardVector() * Value);
	}
}

void AMyPawn::MoveRight(float Value)
{
	//CurrentVelocity.Y += FMath::Clamp(Value, -1.f, 1.f) * MaxSpeed;
	if (MovementComp)
	{
		MovementComp->AddInputVector(GetActorRightVector() * Value);
	}
}

void AMyPawn::Turn(float Value)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += Value;
	SetActorRotation(NewRotation);
}

void AMyPawn::LookUp(float Value)
{
	FRotator NewRotation = CameraBoom->GetComponentRotation();
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + Value, -60.f, 30.f);
	CameraBoom->SetWorldRotation(NewRotation);
}

