// Fill out your copyright notice in the Description page of Project Settings.


#include "SBasePickUp.h"
#include "Components/SphereComponent.h"

// Sets default values
ASBasePickUp::ASBasePickUp()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("PowerUp");
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	//Disable collision, instead we use SphereComp to handle interaction queries
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);

	RespawnTime = 10.f;

	SetReplicates(true);
}

void ASBasePickUp::Interact_Implementation(APawn* InstigatorPawn)
{
	//logic derived in classes
}

void ASBasePickUp::ShowPowerUp()
{
	SetPowerUpState(true);
}

void ASBasePickUp::HideAndCooldownPowerUp()
{
	SetPowerUpState(false);

	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &ASBasePickUp::ShowPowerUp, RespawnTime);
}

void ASBasePickUp::SetPowerUpState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);

	//Set visibility on root and all children
	RootComponent->SetVisibility(bNewIsActive, true);
}
