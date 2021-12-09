// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoinPickUp.h"

#include "SPlayerState.h"

ASCoinPickUp::ASCoinPickUp()
{
	CreditsAmount = 50;
}

void ASCoinPickUp::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	if (ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>())
	{
		PS->AddCredits(CreditsAmount);
		HideAndCooldownPowerUp();
	}
}
