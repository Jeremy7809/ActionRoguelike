// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<AActor> MinionClass;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UEnvQuery* SpawnBotQuery;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UCurveFloat* DifficultyCurve;

	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SpawnTimerInterval;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	int32 CreditsPerKill;
	
	UPROPERTY(EditDefaultsOnly, Category= "PickUps")
	TArray<TSubclassOf<AActor>> PickUpClasses;

	UPROPERTY(EditDefaultsOnly, Category = "PickUps")
	UEnvQuery* SpawnPickUpQuery;

	UPROPERTY(EditDefaultsOnly, Category = "PickUps")
	int32 SpawnPickUpCount;

	UPROPERTY(EditDefaultsOnly, Category = "PickUps")
	float RequiredPickUpDistance;

	UPROPERTY(EditDefaultsOnly, Category = "PickUps")
	FVector SpawnOffset;
	
	UFUNCTION()
	void SpawnBotTimerElapsed();

	UFUNCTION()
	void OnBotQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void OnPickUpQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);
	
public:

	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);
	
	ASGameModeBase();

	virtual void StartPlay() override;

	UFUNCTION(Exec)
	void KillAll();
};
