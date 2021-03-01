// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/C_WeaponAccessory.h"
#include "Components/StaticMeshComponent.h"

AC_WeaponAccessory::AC_WeaponAccessory()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
}