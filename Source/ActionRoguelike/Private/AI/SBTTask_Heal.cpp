// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_Heal.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type USBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();
	if (ensure(MyController))
	{
		ACharacter* MyPawn = Cast<ACharacter>(MyController->GetPawn());
		if (MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(
			MyPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		
		AttributeComp->FullHeal();

		return AttributeComp->HealthMaxed() ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
