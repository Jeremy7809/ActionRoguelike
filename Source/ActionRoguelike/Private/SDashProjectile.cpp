// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASDashProjectile::ASDashProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	ExplodeEffectComp = CreateDefaultSubobject<UParticleSystemComponent>("ExplodeEffectComp");
	ExplodeEffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 6000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_Explode, this, &ASDashProjectile::Explode_TimeElapsed,
	                                0.2f);
}

// Called every frame
void ASDashProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASDashProjectile::Explode_TimeElapsed()
{
	MovementComp->StopMovementImmediately();
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplodeEffectComp->Template, GetActorLocation(), GetActorRotation(),
	                                         GetActorScale(), true, EPSCPoolMethod::None, true);

	GetWorldTimerManager().SetTimer(TimerHandle_Dash, this, &ASDashProjectile::Dash_TimeElapsed,
	                                0.2f);
}

void ASDashProjectile::Dash_TimeElapsed()
{
	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), GetInstigator()->GetActorRotation(), false, false);	
	}
	
	Destroy();
}


void ASDashProjectile::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                 FVector NormalImpulse, const FHitResult& Hit)
{
	TimerHandle_Explode.Invalidate();
	Explode_TimeElapsed();
}
