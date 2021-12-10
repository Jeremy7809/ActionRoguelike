// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*,
                                              OwningComp, float, NewHealth, float, Delta);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnRageChanged, AActor*, InstigatorActor, USAttributeComponent*,
											  OwningComp, float, NewRage, float, Delta);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static USAttributeComponent* GetAttributes(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes", meta = (DisplayName = "IsAlive"))
	static bool IsActorAlive(AActor* Actor);
	
	// Sets default values for this component's properties
	USAttributeComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float HealthMax;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float Rage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Attributes")
	float RageMax;

	// HealthMax, Stamina, Strength

public:

	UFUNCTION(BlueprintCallable)
	bool Kill(AActor* InstigatorActor);
	
	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	bool HealthMaxed() const;

	UFUNCTION(BlueprintCallable)
	bool HealthLow() const;

	UFUNCTION(BlueprintCallable)
	float GetHealthMax() const;

	UFUNCTION(BlueprintCallable)
	float GetRage() const;
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnRageChanged OnRageChanged;

	UFUNCTION(BlueprintCallable, Category= "Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);

	UFUNCTION(BlueprintCallable, Category= "Attributes")
	bool ApplyRageChange(AActor* InstigatorActor, float Delta);
};
