// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoinPickUp.h"

#include "SPlayerState.h"

ASCoinPickUp::ASCoinPickUp()
{
	
}

void ASCoinPickUp::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	ASPlayerState* PS = Cast<ASPlayerState>(InstigatorPawn->GetPlayerState());
	if (ensure(PS) && !PS->CreditsMaxed())
	{
		if (PS->ApplyCreditChange(50.f))
		{
			HideAndCooldownPowerUp();
		}
	}
}
