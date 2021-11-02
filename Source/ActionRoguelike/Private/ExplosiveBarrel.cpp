// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"

#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	RootComponent = StaticMeshComp;
	StaticMeshComp->SetSimulatePhysics(true);
	StaticMeshComp->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	StaticMeshComp->OnComponentHit.AddDynamic(this, &AExplosiveBarrel::OnCompHit);

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComponent");
	RadialForceComp->SetupAttachment(StaticMeshComp);
	RadialForceComp->Radius = 600.0f;
	RadialForceComp->ImpulseStrength = 2000.0f;
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->SetAutoActivate(false);
}


void AExplosiveBarrel::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                 FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
		                                              FString::Printf(TEXT("I hit: %s"), *OtherActor->GetName()));
	}
	RadialForceComp->FireImpulse();

	UE_LOG(LogTemp, Log, TEXT("OnActorHit in Explosive Barrel"));

	
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	FString CombinedString = FString::Printf(TEXT("Hit at location: %s"),*Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(),Hit.ImpactPoint,CombinedString,nullptr,FColor::Green,2.0f,true);
}

// Called when the game starts or when spawned
void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
