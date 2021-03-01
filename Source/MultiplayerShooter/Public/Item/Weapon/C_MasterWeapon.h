// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/C_MasterItem.h"
#include "C_MasterWeapon.generated.h"

/**
 * 
 */

class USkeletalMeshComponent;
class UCameraComponent;

UENUM(BlueprintType)
enum E_WeaponType
{
	E_Prime UMETA(DisplayName = "Prime"),
	E_Second UMETA(DisplayName = "Second"),
	E_Melee UMETA(DisplayName = "Melee"),
	E_WeaponHide UMETA(DisplayName = "Hide") //IsSafetyZone or for hide weapon in the WeaponComponent (hide if need)
};

UENUM(BlueprintType)
enum E_FireMode
{
	E_OneShoot UMETA(DisplayName = "OneShoot"),  //CanAll
	E_OneShoot_Reload UMETA(DisplayName = "OneShoot_Reload"), // For Sniper or Shotgun
	E_Auto UMETA(DisplayName = "Auto"), 
	E_Burst UMETA(DisplayName = "Burst") 
};

UCLASS()
class MULTIPLAYERSHOOTER_API AC_MasterWeapon : public AC_MasterItem
{
	GENERATED_BODY()



		UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* CameraComponent;
		
public:
	AC_MasterWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponInfo)
		TEnumAsByte<E_WeaponType> WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponInfo)
		TEnumAsByte<E_FireMode> FireMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponInfo)
	int maxAmmo = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponInfo)
	int currentAmmo = 30;

	void OnFire(bool isPressed);

	void Fire();
	//UPROPERTY(Replicated)
	bool Reload; //Out of ammo
	
	bool shortReload; //Jammed or a weapon with reload every shots (Shotgun)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponInfo)
	float ShootDelay = 0.1f;

	

private:
	void spawnProjectile();

	bool CanFire();

	bool IsAuto = false;

	bool isReload;

	bool IsPressed;

	bool Jammed = false;

	FTimerHandle _TimerShot;
	
};
