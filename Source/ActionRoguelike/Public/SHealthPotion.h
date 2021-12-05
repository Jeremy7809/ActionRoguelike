// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBasePickUp.h"
#include "SHealthPotion.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ASHealthPotion : public ASBasePickUp
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASHealthPotion();
	
	void Interact_Implementation(APawn* InstigatorPawn) override;
};
