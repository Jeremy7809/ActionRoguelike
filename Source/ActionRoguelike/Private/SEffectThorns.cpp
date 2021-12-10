// Fill out your copyright notice in the Description page of Project Settings.


#include "SEffectThorns.h"

#include "SAttributeComponent.h"
#include "SCharacter.h"
#include "AI/SAICharacter.h"

void USEffectThorns::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ASCharacter* Player = Cast<ASCharacter>(Instigator);
	if (Player)
	{
		USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(Player);
		if (AttributeComp)
		{
			AttributeComp->OnHealthChanged.AddDynamic(this, &USEffectThorns::OnHealthChanged);
		}
	}
}

void USEffectThorns::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);

	ASCharacter* Player = Cast<ASCharacter>(Instigator);
	if (Player)
	{
		USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(Player);
		if (AttributeComp)
		{
			AttributeComp->OnHealthChanged.RemoveDynamic(this, &USEffectThorns::OnHealthChanged);
		}
	}
}

void USEffectThorns::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	int32 DamageBack = Delta * 0.6f;

	ASAICharacter* AI = Cast<ASAICharacter>(InstigatorActor);
	if (AI)
	{
		USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(AI);
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(InstigatorActor, DamageBack);
		}
	}
}

