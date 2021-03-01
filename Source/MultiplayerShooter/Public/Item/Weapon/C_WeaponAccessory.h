// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/C_MasterItem.h"
#include "C_WeaponAccessory.generated.h"

/**
 * 
 */

class UStaticMeshComponent;
UCLASS()
class MULTIPLAYERSHOOTER_API AC_WeaponAccessory : public AC_MasterItem
{
	GENERATED_BODY()

		UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		UStaticMeshComponent* Mesh;
public:
	AC_WeaponAccessory();
	
};
