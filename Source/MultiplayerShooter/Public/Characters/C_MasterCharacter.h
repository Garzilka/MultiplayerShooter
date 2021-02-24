// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_MasterCharacter.generated.h"

class C_StorageComponent;
UCLASS()
class MULTIPLAYERSHOOTER_API AC_MasterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_MasterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnFire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	C_StorageComponent* WeaponComponent;

};
