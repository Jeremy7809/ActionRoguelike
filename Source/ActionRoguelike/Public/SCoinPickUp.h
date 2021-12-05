// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBasePickUp.h"
#include "SCoinPickUp.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASCoinPickUp : public ASBasePickUp
{
	GENERATED_BODY()

public:

	ASCoinPickUp();
	
	void Interact_Implementation(APawn* InstigatorPawn) override;
};
