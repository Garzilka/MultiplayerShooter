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

	void spawnWeapon(TSubclassOf<AC_MasterWeapon> WeaponToSpawn);

	void OnSwitchWeapon(E_WeaponType EType);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(replicated)
	AC_MasterWeapon* CurrentWeapon = nullptr;

	UPROPERTY(replicated)
	AC_MasterWeapon* PrimaryWeapon;
	UPROPERTY(replicated)
	AC_MasterWeapon* SecondaryWeapon;
	UPROPERTY(replicated)
	AC_MasterWeapon* MeleeWeapon;

private:
	void DetachCurrentWeapon();

	void AttachCurrentWeapon(AC_MasterWeapon* NewWeapon);

	AC_MasterCharacter* _Owner;
};
