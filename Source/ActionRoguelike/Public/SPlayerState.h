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
	int32 GetCredits() const;

	UFUNCTION(BlueprintCallable, Category= "Credits")
	void AddCredits(int32 Delta);

	UFUNCTION(BlueprintCallable, Category= "Credits")
	bool RemoveCredits(int32 Delta);

	ASPlayerState();
	
protected:

	UPROPERTY(EditDefaultsOnly, Category= "Credits")
	int32 Credits;
	
};
