// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/C_WeaponComponent.h"
#include "Characters/C_MasterCharacter.h"
#include "Item/Weapon/C_MasterWeapon.h"
#include "Engine/World.h"
#include "Characters/Player/C_Player.h"
// Sets default values for this component's properties
UC_WeaponComponent::UC_WeaponComponent()
{
	SetIsReplicatedByDefault(true);
}
UC_WeaponComponent::UC_WeaponComponent(AC_MasterCharacter* OwnerRef) :
	UC_WeaponComponent()
{
	if (_Owner != nullptr)
		_Owner = OwnerRef;
	_Owner = (AC_MasterCharacter*)GetOwner();

	PrimaryComponentTick.bCanEverTick = true;

	Aiming();


}
void UC_WeaponComponent::GetLifetimeReplicatedProps(TArray < FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UC_WeaponComponent, CurrentWeapon);
	DOREPLIFETIME(UC_WeaponComponent, PrimaryWeapon);
	DOREPLIFETIME(UC_WeaponComponent, SecondaryWeapon);
	DOREPLIFETIME(UC_WeaponComponent, MeleeWeapon);

}
void UC_WeaponComponent::Server_spawnWeapon_Implementation(TSubclassOf<AC_MasterWeapon> WeaponToSpawn)
{
	_Owner = (AC_MasterCharacter*)GetOwner();
	if (GetOwnerRole() == ROLE_Authority)
	{
		FActorSpawnParameters Params;
		FVector LocationForSpawn = _Owner->GetActorLocation();
		AC_MasterWeapon* NewWeapon;
		NewWeapon = GetWorld()->SpawnActor<AC_MasterWeapon>(WeaponToSpawn, FVector(0, 0, 0), FRotator(0.f, 0.f, 0.f), Params);
		if (NewWeapon != nullptr)
		{
			if (NewWeapon->WeaponType == E_WeaponType::E_Prime)
			{
				PrimaryWeapon = NewWeapon;
				PrimaryWeapon->SetActorEnableCollision(false);
				PrimaryWeapon->SetActorHiddenInGame(true);
				if (_Owner != nullptr)
					PrimaryWeapon->TakeIt(_Owner);
			}

		}
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
	Server_OnSwitchWeapon(EType);	
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
		CurrentWeapon = nullptr;
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
void UC_WeaponComponent::Server_OnSwitchWeapon_Implementation(E_WeaponType EType)
{
	
	if (GetOwnerRole() == ROLE_Authority)
	{
		
		E_WeaponType L_SwitchWeapon = EType;
		//If new selected weapon == current weapon -> Hide Weapon
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
			}
			return;
		}
		default:
		{
			return;
		}
		}
	}
	return;
}



void UC_WeaponComponent::OnFire(bool IsPressed)
{
	Server_Fire(IsPressed);
}

void UC_WeaponComponent::Server_Fire_Implementation(bool IsPressed)
{
	if (CurrentWeapon != nullptr)
	{
		CurrentWeapon->OnFire(IsPressed);
		UE_LOG(LogTemp, Warning, TEXT("Call OnFire!"));
	}
}

void UC_WeaponComponent::Aiming()
{
	if (GetOwner() == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("Null"));
	AC_Player* L_IsPlayer = (AC_Player*)GetOwner();
	if (L_IsPlayer != nullptr)
	{
		if(CurrentWeapon != nullptr)
			L_IsPlayer->isAiming = true;
		UE_LOG(LogTemp, Warning, TEXT("Aiming!"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Not Aiming!"));

}