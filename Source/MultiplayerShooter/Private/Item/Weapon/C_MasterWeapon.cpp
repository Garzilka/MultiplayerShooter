// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/C_MasterWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Characters/C_MasterCharacter.h"


AC_MasterWeapon::AC_MasterWeapon()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Mesh->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(Mesh);
}

void AC_MasterWeapon::OnFire(bool isPressed)
{
	if (isPressed) //If true -> fire, if false -> break recursion
	{
		IsPressed = true;
		switch (FireMode)
		{
		case E_OneShoot:
		{
			UE_LOG(LogTemp, Warning, TEXT("E_OneShoot!"));
			spawnProjectile();
			break;
		}
		case E_OneShoot_Reload:
		{
			UE_LOG(LogTemp, Warning, TEXT("E_OneShoot_Reload!"));
			spawnProjectile();
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
				spawnProjectile();
				GetWorld()->GetTimerManager().SetTimer(_TimerShot, this, &AC_MasterWeapon::Fire, ShootDelay, false);
			}
			else
				_Owner->Reload(Jammed && currentAmmo > 0); //if Jammed and have ammo -> short reload
		}
		else
			_Owner->Reload(false);
	}
}
void AC_MasterWeapon::spawnProjectile()
{
	currentAmmo--;
	UE_LOG(LogTemp, Warning, TEXT("Shoot!"));
}
bool AC_MasterWeapon::CanFire() //Perhaps this can be removed
{ 
	return ((IsPressed == true));
}