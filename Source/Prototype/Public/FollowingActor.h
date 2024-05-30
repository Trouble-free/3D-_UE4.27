// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FollowingActor.generated.h"

UCLASS()
class PROTOTYPE_API AFollowingActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh;
	
public:	
	// Sets default values for this actor's properties
	AFollowingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
