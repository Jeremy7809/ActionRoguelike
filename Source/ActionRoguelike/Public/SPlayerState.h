// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, ASPlayerState*,
											  OwningState, float, NewCredit, float, Delta);

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnCreditsChanged OnCreditsChanged;
	
	UFUNCTION(BlueprintCallable, Category= "Credits")
	bool ApplyCreditChange(float Delta);

	ASPlayerState();

	UFUNCTION(BlueprintCallable)
	bool CreditsMaxed() const;

	UFUNCTION(BlueprintCallable)
	bool CreditsNone() const;

	UFUNCTION(BlueprintCallable)
	bool EnoughCredits(float Cost) const;
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Credits")
	float Credits;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Credits")
	float CreditsMax;
	
};
