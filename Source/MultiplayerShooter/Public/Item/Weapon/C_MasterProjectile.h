// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "C_MasterProjectile.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class MULTIPLAYERSHOOTER_API AC_MasterProjectile : public AActor
{
	GENERATED_BODY()
		
public:
	AC_MasterProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	float speed = 10000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	float maxSpeed = 20000;
	// Sets default values for this actor's properties	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USphereComponent* Sphere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* Mesh;

protected:
	void _OnBeginEverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
