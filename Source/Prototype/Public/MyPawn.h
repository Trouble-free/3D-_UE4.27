// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PROTOTYPE_API AMyPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta=(AllowPrivateAccess=true))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta=(AllowPrivateAccess=true))
	UCameraComponent* Camera;

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Follower")
	class AFollowingActor* Follower = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }

	UPROPERTY(VisibleAnywhere)
	class UMyMovementComponent* MovementComp;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

private:
	void MoveForward(float Value);

	void MoveRight(float Value);

	void Turn(float Value);

	void LookUp(float Value);

};
