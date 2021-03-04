// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/C_MasterWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Item/Weapon/C_MasterProjectile.h"
#include "Characters/C_MasterCharacter.h"
#include "Engine/World.h"


AC_MasterWeapon::AC_MasterWeapon()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Mesh->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(Mesh);
}

void AC_MasterWeapon::OnFire(bool isPressed)
{
	UE_LOG(LogTemp, Warning, TEXT("Call onFire!"));
	IsPressed = isPressed;
	if (IsPressed) //If true -> fire, if false -> break recursion
	{
		switch (FireMode)
		{
		case E_OneShoot:
		{
			UE_LOG(LogTemp, Warning, TEXT("E_OneShoot!"));
			Server_spawnProjectile();
			break;
		}
		case E_OneShoot_Reload:
		{
			UE_LOG(LogTemp, Warning, TEXT("E_OneShoot_Reload!"));
			Server_spawnProjectile();
			_Owner->Reload(currentAmmo > 0);
			break;
		}
		case E_Auto:
		{
			UE_LOG(LogTemp, Warning, TEXT("Auto!"));
			Fire();
			break;
		}
		case E_Burst:
		{
			return;
		}
		default:
		{
			return;
		}
		}
	}
	else
	{
		IsPressed = false;
		UE_LOG(LogTemp, Warning, TEXT("ITryStop!"));
		GetWorld()->GetTimerManager().PauseTimer(_TimerShot);
	}
}

void AC_MasterWeapon::Fire()
{
	//This is recursion
	if (IsPressed)
	{
		if (currentAmmo > 0)
		{
			if (!Jammed)
			{
				Server_spawnProjectile();
				GetWorld()->GetTimerManager().SetTimer(_TimerShot, this, &AC_MasterWeapon::Fire, ShootDelay, false);
			}
			else
				_Owner->Reload(Jammed && currentAmmo > 0); //if Jammed and have ammo -> short reload
		}
		else
			_Owner->Reload(false);
	}
}
void AC_MasterWeapon::Server_spawnProjectile_Implementation()
{
	currentAmmo--;
	FActorSpawnParameters Params;
	FVector L_LocationForSpawn = _Owner->GetActorLocation() + _Owner->GetActorForwardVector() * 100;
	GetWorld()->SpawnActor<AC_MasterProjectile>(Projectile, L_LocationForSpawn, _Owner->GetActorRotation(), Params);
	/*AC_MasterProjectile* L_Projectile =*/ 
	/*if (NewWeapon != nullptr)
	{
		if (NewWeapon->WeaponType == E_WeaponType::E_Prime)
		{
			PrimaryWeapon = NewWeapon;
			PrimaryWeapon->SetActorEnableCollision(false);
			PrimaryWeapon->SetActorHiddenInGame(true);
			if (_Owner != nullptr)
				PrimaryWeapon->TakeIt(_Owner);
		}

	}**/
	UE_LOG(LogTemp, Warning, TEXT("Shoot!"));
}
bool AC_MasterWeapon::CanFire() //Perhaps this can be removed
{ 
	return ((IsPressed == true));
}