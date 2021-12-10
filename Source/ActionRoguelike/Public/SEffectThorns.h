// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SActionEffect.h"
#include "SEffectThorns.generated.h"

class USAttributeComponent;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API USEffectThorns : public USActionEffect
{
	GENERATED_BODY()

public:

	void StartAction_Implementation(AActor* Instigator) override;
	
	void StopAction_Implementation(AActor* Instigator) override;

protected:

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);
	
};
