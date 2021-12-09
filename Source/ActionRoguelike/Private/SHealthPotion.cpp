// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"

#include "SAttributeComponent.h"
#include "SPlayerState.h"


// Sets default values
ASHealthPotion::ASHealthPotion()
{
	CreditCost = 100;
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn);

	if (ensure(AttributeComp) && !AttributeComp->HealthMaxed())
	{
		if (ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>())
		{
			if (PS->RemoveCredits(CreditCost) && AttributeComp->ApplyHealthChange(this, 20.f))
			{
				HideAndCooldownPowerUp();
			}
		}
	}
}
