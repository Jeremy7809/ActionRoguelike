// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBasePickUp.h"
#include "SDashPickUp.generated.h"

class USAction;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASDashPickUp : public ASBasePickUp
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	TSubclassOf<USAction> ActionGranted;

public:

	ASDashPickUp();

	void Interact_Implementation(APawn* InstigatorPawn) override;
	
};
