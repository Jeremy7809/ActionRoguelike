// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SBasePickUp.generated.h"

class USphereComponent;

UCLASS()
class ACTIONROGUELIKE_API ASBasePickUp : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

protected:
	bool Active;
	float ActivateDelay;
	FTimerHandle TimerHandle_Activate;
	
public:	

	void Interact_Implementation(APawn* InstigatorPawn) override;
	
	ASBasePickUp();

protected:

	UPROPERTY(ReplicatedUsing="OnRep_IsActive")
	bool bIsActive;

	UFUNCTION()
	void OnRep_IsActive();

	UPROPERTY(EditAnywhere, Category="PowerUp")
	float RespawnTime;

	FTimerHandle TimerHandle_RespawnTimer;

	UFUNCTION()
	void ShowPowerUp();

	void HideAndCooldownPowerUp();

	void SetPowerUpState(bool bNewIsActive);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	USphereComponent* SphereComp;

};
