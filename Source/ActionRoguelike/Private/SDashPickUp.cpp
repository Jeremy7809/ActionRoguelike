// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashPickUp.h"

#include "SAction.h"
#include "SActionComponent.h"

ASDashPickUp::ASDashPickUp()
{
}

void ASDashPickUp::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	USActionComponent* ActionComp = Cast<USActionComponent>(
		InstigatorPawn->GetComponentByClass(USActionComponent::StaticClass()));
	if (ActionComp && ensure(ActionGranted))
	{
		if (!ActionComp->CheckActions(ActionGranted))
		{
			ActionComp->AddAction(InstigatorPawn, ActionGranted);
			HideAndCooldownPowerUp();
		}
	}
}
