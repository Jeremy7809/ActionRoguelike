// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"

#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "SAttributeComponent.h"
#include "SCharacter.h"
#include "SPlayerState.h"
#include "AI/SAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"

static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("su.SpawnBots"), true, TEXT("Enable spawning of bots via timer"),
                                                ECVF_Cheat);

ASGameModeBase::ASGameModeBase()
{
	SpawnTimerInterval = 2.0f;
	SpawnPUCount = 10;
}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();

	//Continious timer to spawn in more bots.
	//Actual amount of bots and whether its allowed to spawn determined by spawn logic later in the chain...
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ASGameModeBase::SpawnBotTimerElapsed,
	                                SpawnTimerInterval, true);

	SpawnPickUps();
}

void ASGameModeBase::KillAll()
{
	for (TActorIterator<ASAICharacter> It(GetWorld()); It; ++It)
	{
		ASAICharacter* Bot = *It;
		USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(Bot);
		if (ensure(AttributeComp) && AttributeComp->IsAlive())
		{
			AttributeComp->Kill(this); // pass in player? for kill credit
		}
	}
}

void ASGameModeBase::SpawnPickUps()
{
	for (int32 NrOfSpawnedPUs = 0; NrOfSpawnedPUs < SpawnPUCount; NrOfSpawnedPUs++)
	{
		if (NrOfSpawnedPUs < 3)
		{
			UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(
				this, SpawnPUQuery, this, EEnvQueryRunMode::RandomBest25Pct, nullptr);
			if (ensure(QueryInstance))
			{
				QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASGameModeBase::OnHealthPUQueryCompleted);
			}
		}
		else
		{
			UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(
				this, SpawnPUQuery, this, EEnvQueryRunMode::RandomBest25Pct, nullptr);
			if (ensure(QueryInstance))
			{
				QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASGameModeBase::OnCoinPUQueryCompleted);
			}
		}
	}
}

void ASGameModeBase::SpawnBotTimerElapsed()
{
	if (!CVarSpawnBots.GetValueOnGameThread())
	{
		UE_LOG(LogTemp, Warning, TEXT("Bot spawning disabled via cvar 'CVarSpawnBots'."))
		return;
	}

	int32 NrOfAliveBots = 0;
	for (TActorIterator<ASAICharacter> It(GetWorld()); It; ++It)
	{
		ASAICharacter* Bot = *It;
		USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(Bot);
		if (ensure(AttributeComp) && AttributeComp->IsAlive())
		{
			NrOfAliveBots++;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Found %i alive bots."), NrOfAliveBots);

	float MaxBotCount = 10.0f;

	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (NrOfAliveBots >= MaxBotCount)
	{
		UE_LOG(LogTemp, Log, TEXT("At maximum bot capacity. Skipping bot spawn."));
		return;
	}

	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(
		this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASGameModeBase::OnBotQueryCompleted);
	}
}

void ASGameModeBase::OnBotQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
                                         EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS Query Failed!"))
		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
	if (Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);

		//Track all the used spawn locations
		DrawDebugSphere(GetWorld(), Locations[0], 50.0f, 20, FColor::Blue, false, 60.0f);
	}
}

void ASGameModeBase::OnHealthPUQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
                                              EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn Health Pick Up EQS Query Failed!"))
		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
	if (Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(HealthPUClass, Locations[0] + SpawnOffset, FRotator::ZeroRotator);

		//Track all the used spawn locations
		DrawDebugSphere(GetWorld(), Locations[0], 50.0f, 20, FColor::Green, false, 60.0f);
	}
}

void ASGameModeBase::OnCoinPUQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
                                            EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn Coin Pick Up EQS Query Failed!"))
		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
	if (Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(CoinPUClass, Locations[0] + SpawnOffset, FRotator::ZeroRotator);

		//Track all the used spawn locations
		DrawDebugSphere(GetWorld(), Locations[0], 50.0f, 20, FColor::Green, false, 60.0f);
	}
}


void ASGameModeBase::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	ASCharacter* PlayerVic = Cast<ASCharacter>(VictimActor);
	ASAICharacter* AIEnemyVic = Cast<ASAICharacter>(VictimActor);
	ASCharacter* PlayerKiller = Cast<ASCharacter>(Killer);

	if (PlayerVic)
	{
		FTimerHandle TimerHandle_RespawnDelay;

		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElapsed", PlayerVic->GetController());

		float RespawnDelay = 2.0f;
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnDelay, false);
		return;
	}
	if (AIEnemyVic && PlayerKiller)
	{
		ASPlayerState* PS = Cast<ASPlayerState>(PlayerKiller->GetPlayerState());
		if (PS)
		{
			PS->ApplyCreditChange(75.f);
		}
		else
			UE_LOG(LogTemp, Log, TEXT("PlayerState not found!!"));
	}

	UE_LOG(LogTemp, Log, TEXT("OnActorKilled: Victim %s, Killer %s"), *GetNameSafe(VictimActor), *GetNameSafe(Killer));
}

void ASGameModeBase::RespawnPlayerElapsed(AController* Controller)
{
	if (ensure(Controller))
	{
		Controller->UnPossess();

		RestartPlayer(Controller);
	}
}
