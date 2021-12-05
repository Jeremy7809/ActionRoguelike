// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"



ASPlayerState::ASPlayerState()
{
	CreditsMax = 1000.0f;
	Credits = 0.0f;
}

bool ASPlayerState::CreditsMaxed() const
{
	return Credits == CreditsMax;
}

bool ASPlayerState::CreditsNone() const
{
	return Credits == 0.0f;
}

bool ASPlayerState::EnoughCredits(float Cost) const
{
	return Credits >= Cost;
}

bool ASPlayerState::ApplyCreditChange(float Delta)
{
	float OldCredits = Credits;

	Credits = FMath::Clamp(Credits + Delta, 0.0f, CreditsMax);

	float ActualDelta = Credits - OldCredits;
	OnCreditsChanged.Broadcast(this, Credits, ActualDelta);

	return ActualDelta != 0;
}

