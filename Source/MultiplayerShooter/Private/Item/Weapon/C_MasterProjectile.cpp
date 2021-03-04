// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/C_MasterProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
AC_MasterProjectile::AC_MasterProjectile()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SpringArm"));
	Sphere->SetupAttachment(GetRootComponent());
	Sphere->SetGenerateOverlapEvents(true);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AC_MasterProjectile::_OnBeginEverlap);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Camera"));
	Mesh->SetupAttachment(Sphere);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	ProjectileMovement->InitialSpeed = speed;
	ProjectileMovement->MaxSpeed = maxSpeed;
	
}
void AC_MasterProjectile::_OnBeginEverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Event!"));
}
// Called when the game starts or when spawned
void AC_MasterProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_MasterProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

