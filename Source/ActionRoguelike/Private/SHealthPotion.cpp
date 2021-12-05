// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"

#include "SAttributeComponent.h"
#include "SPlayerState.h"


// Sets default values
ASHealthPotion::ASHealthPotion()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	//Disable collision, instead we use SphereComp to handle interaction queries
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn);
	ASPlayerState* PS = Cast<ASPlayerState>(InstigatorPawn->GetPlayerState());
	if (ensure(AttributeComp) && !AttributeComp->HealthMaxed() && PS->EnoughCredits(100.0f))
	{
		if (AttributeComp->ApplyHealthChange(this, 20.f) && PS->ApplyCreditChange(-100.0f))
		{
			HideAndCooldownPowerUp();
		}
	} 
}
