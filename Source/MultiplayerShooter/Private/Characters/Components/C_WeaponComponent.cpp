// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/C_WeaponComponent.h"
#include "Characters/C_MasterCharacter.h"
#include "Item/Weapon/C_MasterWeapon.h"

#include "Engine/World.h"
// Sets default values for this component's properties
UC_WeaponComponent::UC_WeaponComponent()
{
}
UC_WeaponComponent::UC_WeaponComponent(AC_MasterCharacter* OwnerRef) : 
	UC_WeaponComponent()
{
	_Owner = OwnerRef;
	
	FActorSpawnParameters Params;
	FVector LocationForSpawn = _Owner->GetActorLocation();

	PrimaryWeapon = GetWorld()->SpawnActor<AC_MasterWeapon>(LocationForSpawn, FRotator(0.f, 0.f, 0.f), Params); //ћакрос находитс€ в MasterCharacter
	if (PrimaryWeapon != nullptr)
	{
		PrimaryWeapon->SetActorEnableCollision(false);
		PrimaryWeapon->SetActorHiddenInGame(true);
		PrimaryComponentTick.bCanEverTick = true;
	}
}

// Called when the game starts
void UC_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UC_WeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UC_WeaponComponent::OnSwitchWeapon(E_WeaponType EType)
{
	E_WeaponType L_SwitchWeapon = EType;
	DetachCurrentWeapon();
	//≈сли выбор нового оружи€ равен выбору старого оружи€ -> скрыть оружие
	if (CurrentWeapon != nullptr)
		if (CurrentWeapon->WeaponType == EType)
			L_SwitchWeapon = E_WeaponType::E_WeaponHide;

	switch (L_SwitchWeapon)
	{
	case E_Prime:
	{
		if (PrimaryWeapon != nullptr)
		{
			 
			AttachCurrentWeapon(PrimaryWeapon);
		}
			
		return;
	}
	case E_Second:
	{
		//if (SecondaryWeapon != nullptr)
			//CurrentWeapon = SecondaryWeapon;
		return;
	}
	case E_Melee:
	{
		//if (MeleeWeapon != nullptr)
			//CurrentWeapon = MeleeWeapon;
		return;
	}
	case E_WeaponHide:
	{
		if (MeleeWeapon != nullptr)
		{
			DetachCurrentWeapon();
			CurrentWeapon = MeleeWeapon;
		}
		return;
	}
	default:
	{
		return;
	}
	}
}

void UC_WeaponComponent::DetachCurrentWeapon()
{
	if (CurrentWeapon != nullptr)
	{
		FDetachmentTransformRules L_DetachTransform(EDetachmentRule::KeepRelative, false);
		CurrentWeapon->DetachFromActor(L_DetachTransform);
		CurrentWeapon->SetActorHiddenInGame(true);
		FAttachmentTransformRules L_AttachTransform(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);
		CurrentWeapon->AttachToComponent(_Owner->GetMesh(), L_AttachTransform, "");
	}
	
}

void UC_WeaponComponent::AttachCurrentWeapon(AC_MasterWeapon* NewWeapon)
{
	if (_Owner != nullptr && (CurrentWeapon != NewWeapon && NewWeapon != nullptr))
	{
		CurrentWeapon = NewWeapon;
		CurrentWeapon->SetActorHiddenInGame(false);		
		FAttachmentTransformRules AttachTransform(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, false);		
		CurrentWeapon->AttachToComponent(_Owner->GetMesh(), AttachTransform, "SKT_Gun");
	}
}