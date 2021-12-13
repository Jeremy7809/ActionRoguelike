// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashPickUp.h"
#include "SAction.h"
#include "SActionComponent.h"

ASDashPickUp::ASDashPickUp()
{
}

void ASDashPickUp::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn && ActionGranted))
	{
		return;
	}

	USActionComponent* ActionComp = Cast<USActionComponent>(
		InstigatorPawn->GetComponentByClass(USActionComponent::StaticClass()));
	if (ActionComp)
	{
		if (ActionComp->CheckActions(ActionGranted))
		{
			FString DebugMsg = FString::Printf(TEXT("Action '%s' already known."), *GetNameSafe(ActionGranted));
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, DebugMsg);
			return;
		}
		
		// Give new ability
		ActionComp->AddAction(InstigatorPawn, ActionGranted);
		HideAndCooldownPowerUp();
	}
}
