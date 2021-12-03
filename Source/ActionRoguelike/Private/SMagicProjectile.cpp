// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include "SAttributeComponent.h"
#include "SGameplayFunctionLibrary.h"
#include "CollisionAnalyzer/Public/ICollisionAnalyzer.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);

	ProjectileDamage = 10.f;
}


void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                       const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		/*Explode();
		
		USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(OtherActor);
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(GetInstigator(), -ProjectileDamage);

			Destroy();
		}*/

		if (USGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, ProjectileDamage,
		                                                      SweepResult))
		{
			Explode();
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSFX, OtherActor->GetActorLocation(),
			                                      GetActorRotation(),
			                                      1.f, 1.f, 0.f, nullptr, nullptr, nullptr);
			if (ensure(CamShake))
				UGameplayStatics::PlayWorldCameraShake(GetWorld(), CamShake, OtherActor->GetActorLocation(), 0.f,
				                                       50000.f, 1,
				                                       false);
		}
	}
}
