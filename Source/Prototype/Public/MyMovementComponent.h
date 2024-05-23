// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MyMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UMyMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	UMyMovementComponent();

	UPROPERTY(EditAnywhere)
	float MaxSpeed;

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
