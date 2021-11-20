// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SBasePickUp.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASBasePickUp : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* InstigatorPawn);

protected:
	bool Active;
	float ActivateDelay;
	FTimerHandle TimerHandle_Activate;
	
public:	
	// Sets default values for this actor's properties
	ASBasePickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;
	
	void Deactivate();
	
	void Deactivate_TimeElapsed();

	bool IsActive();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
