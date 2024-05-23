// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewTargetActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AViewTargetActor::AViewTargetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));

}

// Called when the game starts or when spawned
void AViewTargetActor::BeginPlay()
{
	Super::BeginPlay();

	OverlapBox->SetGenerateOverlapEvents(true);
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AViewTargetActor::OnOverlapBegin);
	OverlapBox->OnComponentEndOverlap.AddDynamic(this, &AViewTargetActor::OnOverlapEnd);

	PC = UGameplayStatics::GetPlayerController(this, 0);
}

void AViewTargetActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// set view target with blend
	if (ViewTarget && PC)
	{
		PC->SetViewTargetWithBlend(ViewTarget, BlendTime);
		bIsOverlapped = true;

#if 1
		if (!bIsDynamic)
		{
			FLatentActionInfo LatentInfo;
			LatentInfo.CallbackTarget = this;
			LatentInfo.ExecutionFunction = "AfterDelay";
			LatentInfo.Linkage = 0;
			LatentInfo.UUID = __LINE__;
			UKismetSystemLibrary::Delay(this, 1.f, LatentInfo);
		}
#endif
	}
}

void AViewTargetActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ViewTarget && PC)
	{
		PC->SetViewTargetWithBlend(PC->GetPawn(), BlendTime);
		bIsOverlapped = false;
	}
}

void AViewTargetActor::AfterDelay()
{
	FRotator Rot = UKismetMathLibrary::FindLookAtRotation(ViewTarget->GetActorLocation(), PC->GetPawn()->GetActorLocation());
	PC->SetControlRotation(Rot);
}

// Called every frame
void AViewTargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ViewTarget || !bIsDynamic)
	{
		return;
	}

	if (bIsOverlapped)
	{
		FRotator Rot = UKismetMathLibrary::FindLookAtRotation(ViewTarget->GetActorLocation(), PC->GetPawn()->GetActorLocation());
		ViewTarget->SetActorRotation(Rot);

		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		LatentInfo.ExecutionFunction = "AfterDelay";
		LatentInfo.Linkage = 0;
		LatentInfo.UUID = __LINE__;
		UKismetSystemLibrary::Delay(this, 1.f, LatentInfo);
	}
}

