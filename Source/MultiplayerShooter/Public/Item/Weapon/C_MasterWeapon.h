// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/C_MasterItem.h"
#include "C_MasterWeapon.generated.h"

/**
 * 
 */
/*
UENUM(BlueprintType)
enum E_WeaponType
{
	E_Prime UMETA(DisplayName = "Prime"),
	E_Second UMETA(DisplayName = "Second"),
	E_Melee UMETA(DisplayName = "Melee")
};
*/
UCLASS()
class MULTIPLAYERSHOOTER_API AC_MasterWeapon : public AC_MasterItem
{
	GENERATED_BODY()

public:
	//E_WeaponType* WeaponType;
	
};
