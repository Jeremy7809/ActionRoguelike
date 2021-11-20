// Fill out your copyright notice in the Description page of Project Settings.


#include "SBasePickUp.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASBasePickUp::ASBasePickUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	ActivateDelay = 10.f;
	Active = true;
}

// Called when the game starts or when spawned
void ASBasePickUp::BeginPlay()
{
	Super::BeginPlay();
}


void ASBasePickUp::Deactivate()
{
	MeshComp->SetVisibility(false);
	Active = false;

	GetWorldTimerManager().SetTimer(TimerHandle_Activate, this, &ASBasePickUp::Deactivate_TimeElapsed, ActivateDelay);
}

void ASBasePickUp::Deactivate_TimeElapsed()
{
	MeshComp->SetVisibility(true);
	Active = true;
}


bool ASBasePickUp::IsActive()
{
	return Active;
}

// Called every frame
void ASBasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
