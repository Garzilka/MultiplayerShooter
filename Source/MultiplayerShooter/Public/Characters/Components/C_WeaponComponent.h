// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_WeaponComponent.generated.h"

enum E_WeaponType;
class AC_MasterCharacter;
class AC_MasterWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MULTIPLAYERSHOOTER_API UC_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_WeaponComponent();
	UC_WeaponComponent(AC_MasterCharacter* OwnerRef);

	void OnSwitchWeapon(E_WeaponType EType);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AC_MasterWeapon* CurrentWeapon = nullptr;

	AC_MasterWeapon* PrimaryWeapon;
	AC_MasterWeapon* SecondaryWeapon;
	AC_MasterWeapon* MeleeWeapon;

private:
	void DetachCurrentWeapon();

	void AttachCurrentWeapon(AC_MasterWeapon* NewWeapon);

	AC_MasterCharacter* _Owner;
};
